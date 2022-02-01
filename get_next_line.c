/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <rdavila@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:28:50 by rdavila           #+#    #+#             */
/*   Updated: 2022/02/01 11:16:35 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	output;

	output = 0;
	while (*str != '\0')
	{
		output++;
		str++;
	}
	return (output);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i < len)
	{
		if (i < ft_strlen(s1))
			str[i] = s1[i];
		else
			str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr( const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*ptr;
	int		len;

	len = 0;
	while (s1[len])
		len ++;
	str = malloc (len + 1);
	if (!str)
		return (0);
	ptr = str;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (str);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}


char	*ft_get_line(char	**line)
{
	int		i;
	char	*string;
	char	*newstring;
	i = 0;
	
	while(*line[i] != '\n' && *line[i] != 0)
	{
		i++;
	}
	string = ft_substr(*line, 0, i);
	newstring = ft_substr(*line, i + 1, ft_strlen(*line) - i - 1);
	free(*line);
	*line = newstring;
	return (string);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*output;
	static char	*line;
	ssize_t		readlen;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	readlen = read(fd, buf, BUFFER_SIZE);
	while (readlen > 0)
	{
		buf [readlen] = 0;
		line = ft_strjoin (line, buf);
		if (ft_strchr(line, '\n'))
			break ;
		readlen = read(fd, buf, BUFFER_SIZE);
	}
	output = ft_get_line(&line); //output = ft_get_line
	free(buf);
	return(output);
}

int	main()
{
	int fd;
	fd = open("main.txt", O_RDONLY);
	char *junkie;
	junkie = get_next_line(fd);
	while (junkie != NULL)
	{
		printf("%s \n", junkie);
		junkie = get_next_line(fd);
	}
	return (0);
}