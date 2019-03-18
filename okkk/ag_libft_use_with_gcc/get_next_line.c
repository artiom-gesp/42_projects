/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:24:50 by agesp             #+#    #+#             */
/*   Updated: 2019/02/11 13:08:25 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_n_pos(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*remove_start(char *s)
{
	int i;

	i = 0;
	if (ft_strchr(s, '\n'))
	{
		s = ft_strcpy(s, ft_strchr(s, '\n') + 1);
		return (s);
	}
	if (get_n_pos(s) > 0)
	{
		s = ft_strcpy(s, ft_strchr(s, '\0'));
		return ("\0");
	}
	return (NULL);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*stock_fd[4865];
	char		buff[BUFF_SIZE + 1];
	char		*save;

	if (!line || fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	if (!stock_fd[fd] && (stock_fd[fd] = ft_strnew(0)) == NULL)
		return (-1);
	while (!(ft_strchr(stock_fd[fd], '\n'))
			&& (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		save = stock_fd[fd];
		stock_fd[fd] = ft_strjoin(save, buff);
		free(save);
	}
	*line = ft_strsub(stock_fd[fd], 0, get_n_pos(stock_fd[fd]));
	if (!(remove_start(stock_fd[fd])))
		return (0);
	return (1);
}
