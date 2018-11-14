/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:46:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/14 17:45:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

char	*check_for_endline(char *buff, char **line, int *j, int *k)
{
	size_t i = 0;
	//char *save;
	char	*my_return;
	int flag = 0;
	my_return = ft_strdup(buff);
	while (buff[i] && !flag)
	{
		if (buff[i] == '\n')
		{
			my_return = ft_strncpy(my_return, buff, i + 1);
			my_return[i] = '\0';
			flag = 1;
			*j = 1;
		}
		i++;
	}
	*k = i;
	if (flag == 0)
		my_return = ft_strcpy(my_return, buff);
	ft_strcat(*line, my_return);
	return (&my_return[i]);
}
:
char	*read_once(const int fd)
{
	int ret;
	char *buff;

	if (!(buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	ret = 0;

	ret = read(fd, buff, BUFF_SIZE);
	if (ret == -1)
		return (NULL);
	if (ret == 0)
		return ("-1");
	buff[ret] = '\0';
	return (buff);
}

int	get_next_line(const int fd, char **line)
{
	int i;
	int k;
	static char *save;
	char *save_rest;
	char fake_buff[1];

	i = 0;
	k = 0;
	ft_memset(*line, '\0', sizeof(*line));
	while (i == 0)
	{
		if (save)
			ft_strcat(save, save_rest);
		else
			save = ft_strdup(*line);
		save = *line;
		save_rest = check_for_endline(read_once(fd), line, &i, &k);
	}

	*line = save;
	printf("%s\n", *line);
	if (!(read(fd, fake_buff, 0)))
		return (0);

	return (1);
}

int	main(int ac, char **av)
{
	int fd;
	char *baobab;

	baobab = ft_memalloc(1000000);
	if (ac > 1)
	{
		int i= -1;
		fd = open(av[1], O_RDONLY);
		while (++i < ft_atoi(av[2]))
		{
			get_next_line(fd, &baobab);
		}
	}
	free(baobab);
}
