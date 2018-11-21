/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:11:04 by agesp             #+#    #+#             */
/*   Updated: 2018/11/21 11:34:51 by agesp            ###   ########.fr       */
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

int		make_or_read(char **line, int *ret, t_mylist *list, int c)
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
	*ret = read(list->fd, list->buff, BUFF_SIZE);
	if (*ret == -1)
		return (-1);
	list->buff[*ret] = '\0';
	save = ft_strdup(list->save_my_buff);
	list->save_my_buff = ft_memalloc(ft_strlen(save) + ft_strlen(list->buff));
	ft_strcat(list->save_my_buff, save);
	ft_strcat(list->save_my_buff, list->buff);
	return (0);
}

t_mylist	*multi_fd(int fd, t_mylist *list)
{
	while (list->prev)
		list = list->prev;
	while (list->next)
	{
		if (list->fd == (int)fd)
			return (list);
		list = list->next;
	}
	if (!list->fd)
	{
		list->fd = (int)fd;
		list->prev = NULL;
		return (list);
	}
	if (!list->next)
	{
		list->next = malloc(sizeof(t_mylist));
		list->next->prev = list;
		list->next->next = NULL;
		list->next->fd = (int)fd;
	}
	return (list->next);
}

int		get_next_line(int const fd, char **line)
{
	int				ret;
	static t_mylist	list;

	list = *multi_fd(fd, &list);
	if (!list.flag)
		list.flag = 0;
	ret = 1;
	if (!line || list.fd < 0)
		return (-1);
	while (ret >= 0 && !list.flag)
	{
		if (list.save_my_buff)
		{
			if (ft_strchr(list.save_my_buff, '\n') || ret == 0)
				return (make_or_read(line, &ret, &list,  1));
			else
			{
				if (make_or_read(line, &ret, &list, 0) == -1)
					return (-1);
			}
		}
		else
			list.save_my_buff = ft_memalloc(1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	char *str;
	int i;
	int fd = open(av[1], O_RDONLY);
	int fd2 = open(av[2], O_RDONLY);
	/*	while ((i = get_next_line(fd, &str)))
		{
		printf("%s\n", str);
		}*/
	get_next_line(fd, &str);
	printf("cc%s\n", str);
	get_next_line(fd2, &str);
	printf("dd%s\n", str);
	get_next_line(fd, &str);
	printf("gg%s\n", str);
	get_next_line(fd2, &str);
	printf("pp%s\n", str);

}
