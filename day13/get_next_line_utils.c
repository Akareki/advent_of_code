/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:02:33 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/21 14:42:40 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_isinbuf(const char *str, char c)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_linelen(const char *line)
{
	size_t	len;

	len = 0;
	while (line[len])
		len++;
	return (len);
}

size_t	ft_buflen(const char *buf)
{
	size_t	len;

	len = 0;
	while (len < BUFFER_SIZE && buf[len] && buf[len] != '\n')
		len++;
	if (len < BUFFER_SIZE && buf[len] == '\n')
		return (len + 1);
	return (len);
}

char	*ft_linejoin(const char *line, const char *buf)
{
	size_t	i;
	size_t	j;
	char	*join;

	join = malloc((ft_linelen(line) + ft_buflen(buf) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	while (line[i])
	{
		join[i] = line[i];
		i++;
	}
	j = 0;
	while (j < BUFFER_SIZE && buf[j] && buf[j] != '\n')
	{
		join[j + i] = buf[j];
		j++;
	}
	if (j < BUFFER_SIZE && buf[j] == '\n')
		join[j + i++] = '\n';
	join[i + j] = '\0';
	return (join);
}

void	ft_cleanbuf(char *buf)
{
	size_t	i;
	size_t	buflen;

	i = 0;
	if (!buf[0])
		return ;
	buflen = ft_buflen(buf);
	while (i < BUFFER_SIZE)
	{
		if ((i + buflen < BUFFER_SIZE))
			buf[i] = buf[i + buflen];
		else
			buf[i] = '\0';
		i++;
	}
}
