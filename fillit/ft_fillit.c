/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:58:10 by agesp             #+#    #+#             */
/*   Updated: 2018/11/22 16:27:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fillit.h"

int		get_error(char *str)
{
}

int		read_all(int fd)
{
	int		ret;
	int		i;
	char *buff;
	char *line;

	buff = ft_strnew(5);
	line = ft_strnew(5);
	i = 0;
	while ((ret = read(fd, buff, 5)))
	{
		buff[ret] = '\0';
		if (buff[ret - 1] && buff[ret - 1] != '\n')
			return (-1);
		line = ft_strjoin(line, buff);
		if (i % 4 == 0 && buff[0] != '\n')
			return (-1);
		i++;
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] != '\n' || line[i] != '.' || line[i] != '#')
			return (-1);
	}
	return (0);
}

#include <stdio.h>

int main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);
	printf("%d\n", read_all(fd));
}

