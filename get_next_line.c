/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <rdavila@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:28:50 by rdavila           #+#    #+#             */
/*   Updated: 2022/02/02 12:53:22 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_get_line(char	**line)
{
	int		i;
	char	*string;
	char	*newstring;
	i = 0;

	while((*line)[i] != '\n' && (*line)[i] != 0)
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
	return (output);
}

/*int	main()
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
}*/