/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:46:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/13 17:28:18 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

int	read_all(const int fd, char **line)
{
	static int i = -1;
	char **save;
	int ret;

	ret = 1;
	char buff[BUFF_SIZE];
	ft_memset(buff,'\0', BUFF_SIZE);
	while (ret > 0)
	{
		ret = read(fd, buff, BUFF_SIZE -1);
		printf("%s", buff);
		ft_strcat(*line, buff);
	}
	//printf("%s",*line);
	//	*line = save;
	save = ft_strsplit(*line, '\n');
	while (save[++i])
		printf("%s\n", save[i]);
	return i;
}

int	main(int ac, char **av)
{
	int fd;
	char *baobab;

	baobab = ft_memalloc(1000000);
	if (ac > 1)
	{
		fd = open(av[1], O_RDONLY);
		int i = -1;
		//	while (++i < 3)
		read_all(fd, &baobab);

	}
}
