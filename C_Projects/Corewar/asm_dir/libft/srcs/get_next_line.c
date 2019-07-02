/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:31:12 by amanuel           #+#    #+#             */
/*   Updated: 2018/09/26 02:29:05 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

int		get_next_line(int fd, char **line)
{
	static char		**s = NULL;
	char			*b;
	int				i;

	if ((i = -1) && BUFF_SIZE > 0 && line && fd >= 0 && fd <= OPEN_MAX)
		if (s || (s = ft_memalloc(OPEN_MAX + 1)))
			if (s[fd] || (s[fd] = ft_strnew(BUFF_SIZE)))
				i = 1;
	while ((i > 0) && ft_findc(s[fd], '\n') < 0 && (b = ft_strnew(BUFF_SIZE)))
		if ((i = read(fd, (void*)b, BUFF_SIZE)) >= 0)
			if (!(s[fd] = ft_strjoin_free(s[fd], b, 3)))
				i = -1;
	if (i >= 0 && ft_strlen(s[fd]) && (i = ft_findc(s[fd], '\n') + 1) >= 0)
		if (i || (i = ft_strlen(s[fd]) + 1))
			if (!(*line = ft_strndup(s[fd], i - 1)))
				i = -1;
	if (i > 0)
		ft_strndel(&s[fd], ft_strlen(*line) + 1);
	if ((i > 1 && (i = 1)) && (i == 0 || (i == 1 && !ft_strlen(s[fd]))))
		ft_memdel((void*)&s[fd]);
	return (i);
}
