/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:11:04 by agesp             #+#    #+#             */
/*   Updated: 2018/11/20 13:59:18 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_strccat(char *dst, const char *src, int c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dst[i + j] = src[j];
		if (src[j] == c)
		{
			dst[i + j] = '\0';
			return (1);
		}
		j++;
	}
	dst[i + j] = '\0';
	return (0);
}

char	*remove_start_or_ccpy(char *dst, const char *src, int c, char *s)
{
	int i;

	i = 0;
	if (c == 1)
	{
		while (s[i] && s[i] != '\n')
			i++;
		return (char*)&s[i + 1];
	}
	while (src[i])
	{
		if (src[i] == '\n')
		{
			dst[i] = '\0';
			return (dst);
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int		make_line(char **line, int ret, my_list *list)
{
	*line = remove_start_or_ccpy(list->save_my_buff, list->save_my_buff, 0, "");
	if (ret != 0)
		list->save_my_buff = remove_start_or_ccpy("", "", 1, list->save_my_buff);
	if (ft_strcmp(list->save_my_buff, "") == 0 && ret == 0)
		return (0);
	if (ret == 0 && !(ft_strchr(list->save_my_buff, '\n')))
		list->flag = 1;
	return (1);
}

int		read_line(int *ret, int fd, my_list *list, char *buff)
{
	*ret = read(fd, buff, BUFF_SIZE);
	if (*ret == -1)
		return (-1);
	buff[*ret] = '\0';
	ft_strccat(list->save_my_buff, buff, '\0');
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	int ret;
	char		buff[BUFF_SIZE + 1];
	static my_list list;
	list.flag = 0;

	ret = 1;
	if (!line || fd < 0)
		return (-1);
	while (ret >= 0 && !list.flag)
	{
		if (list.save_my_buff)
		{
			if (ft_strchr(list.save_my_buff, '\n') || ret == 0)
				return (make_line(line,  ret, &list));
			else
			{
				if (read_line(&ret, fd, &list, buff))
					return (0);
			}
		}
		else
			list.save_my_buff = ft_memalloc(sizeof(buff));
	}
	return (0);
}
/*
int		main(int ac, char **av)
{
	char *str;
	int fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &str))
		printf("%s\n", str);
}*/
