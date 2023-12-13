/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:59:53 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/22 10:00:54 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_linecat(char *line, char *buf)
{
	char	*linetemp;

	linetemp = line;
	line = ft_linejoin(line, buf);
	free(linetemp);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_build_next_line(int fd, char *line, char *buf)
{
	ssize_t	bytes_read;

	if (buf)
		line = ft_linecat(line, buf);
	if (!line)
		return (NULL);
	while (!ft_isinbuf(buf, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && !line[0]))
		{
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			return (line);
		if (bytes_read < BUFFER_SIZE)
			buf[bytes_read] = '\0';
		line = ft_linecat(line, buf);
		if (!line)
			return (NULL);
	}
	return (line);
}

void	ft_init_bufline(int fd, char **buf)
{
	ssize_t	i;

	if (*buf)
		return ;
	*buf = malloc(BUFFER_SIZE * sizeof(char));
	if (!(*buf))
		return ;
	i = read(fd, *buf, BUFFER_SIZE);
	if (i == 0 || i == -1)
	{
		free(*buf);
		*buf = NULL;
		return ;
	}
	while (i < BUFFER_SIZE)
		(*buf)[i++] = '\0';
	return ;
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_init_bufline(fd, &buf);
	if (!buf)
		return (NULL);
	line = malloc(sizeof(char));
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	line[0] = '\0';
	line = ft_build_next_line(fd, line, buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	ft_cleanbuf(buf);
	return (line);
}
