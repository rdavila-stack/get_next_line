/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <rdavila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:28:50 by rdavila           #+#    #+#             */
/*   Updated: 2022/01/26 13:18:01 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	char				*dest;
	unsigned int		total;
	unsigned int		i;

	total = count * size;
	dest = malloc(total);
	if (!dest)
		return (0);
	i = 0;
	while (total--)
	{
		dest[i] = 0;
		i++;
	}
	return ((void *)dest);
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


char	*get_next_line(int fd)
{
	char		*buf;
	static char	*line;
	ssize_t		readlen;

	buf = ft_calloc((BUFFER_SIZE + 1) * sizeof (*buf));
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
		//return (line); 
	}
	free(buf);
	return(&line);
	
}

int	main()
{
	int fd;
	fd = open("main.txt", O_RDONLY);
	char *junkie;
	junkie = get_next_line(fd);
	
	while (junkie != NULL)
	{
		junkie = get_next_line(fd);
		printf("%s \n", junkie);
	}
	return (0);
}