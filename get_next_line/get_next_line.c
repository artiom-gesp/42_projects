/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:11:04 by agesp             #+#    #+#             */
/*   Updated: 2018/11/20 17:22:49 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*remove_start(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (char*)&s[i + 1];
}

int		make_or_read(char **line, int *ret, my_list *list, char *buff, int c)
{
	char *save;

	save = NULL;
	if (c == 1)
	{
		*line = ft_strccpy(list->save_my_buff, list->save_my_buff, '\n');
		if (*ret != 0)
			list->save_my_buff = remove_start(list->save_my_buff);
		if (ft_strcmp(list->save_my_buff, "") == 0 && *ret == 0)
			return (0);
		if (*ret == 0 && !(ft_strchr(list->save_my_buff, '\n')))
			list->flag = 1;
		return (1);
	}
	else
	{
		*ret = read(list->fd, buff, BUFF_SIZE);
		if (*ret == -1)
			return (-1);
		buff[*ret] = '\0';
		save = ft_strdup(list->save_my_buff);
	//	ft_memdel((void**)list->save_my_buff);
		list->save_my_buff = ft_memalloc(ft_strlen(save) + ft_strlen(buff));
		ft_strcat(list->save_my_buff, save);
		ft_strcat(list->save_my_buff, buff);
		return (0);
	}
}

my_list	*multi_fd(int fd, my_list *list)
{
	while (list->prev)
		list = list->prev;
	while (list->next)
	{
		if (list->fd == (int)fd)
			return (list);
		list = list->next;
	}
	if (!list->next)
	{
		list->next = malloc(sizeof(my_list));
		list->next->prev = list;
		list->fd = (int)fd;
	}
	return (list);
}



int		get_next_line(int const fd, char **line)
{
	int				ret;
	char			buff[BUFF_SIZE + 1];
	static my_list	list;

	list = *multi_fd(fd, &list);
	if (!list.flag)
		list.flag = 0;
	list.fd = (int)fd;
	ret = 1;
	if (!line || list.fd < 0)
		return (-1);
	while (ret >= 0 && !list.flag)
	{
		if (list.save_my_buff)
		{
			if (ft_strchr(list.save_my_buff, '\n') || ret == 0)
				return (make_or_read(line, &ret, &list, buff, 1));
			else
			{
				if (make_or_read(line, &ret, &list, buff, 0) == -1)
					return (-1);
			}
		}
		else
			list.save_my_buff = ft_memalloc(1);
	}
	return (0);
}
/*
int		main(int ac, char **av)
{
	char *str;
	int i;
	int fd = open(av[1], O_RDONLY);
	int fd2
	while ((i = get_next_line(fd, &str)))
	{
		printf("%s\n", str);
	}
}*/
