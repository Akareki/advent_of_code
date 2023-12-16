/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:54:58 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/21 11:05:41 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	ft_cleanbuf(char *buf);
char	*ft_linejoin(const char *line, const char *buf);
size_t	ft_buflen(const char *buf);
size_t	ft_linelen(const char *line);
int		ft_isinbuf(const char *str, char c);

#endif
