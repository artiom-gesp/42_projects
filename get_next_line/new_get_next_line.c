/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:11:04 by agesp             #+#    #+#             */
/*   Updated: 2018/11/15 17:23:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int ft_strccat(char *dst, char* src, int c)
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

char *remove_start(char *save_my_buff)
{
	int i;

	i = 0;
	while (save_my_buff[i] && save_my_buff[i] != '\n')
		i++;
	return (char*)&save_my_buff[i + 1];
}

int		get_next_line(int const fd, char **line)
{
	int i = 0;
	int flag = 0;
	int ret;
	char buff[BUFF_SIZE + 1];
	static char *save_my_buff;
	ft_memset(*line, '\0', sizeof(*line));
	ret = 1;
	while (ret > 0 && !flag)
	{
		/*if (!save_my_buff)
		{
			save_my_buff = ft_strdup(*line);
			ret = read(fd, buff, BUFF_SIZE);
			while (buff[i])
			{
				if (buff[i] == '\n')
				{
					ft_strccat(*line, buff, '\n');
			//		printf("%s\n", *line);
					ft_strccat(save_my_buff, &buff[i], '\0');
					return (1);
				}
				i++;
			}
		}
		else
		{
		*/	
			//printf("%s\n", save_my_buff);
			if (save_my_buff)
			{
				if (ft_strchr(save_my_buff, '\n'))
				{
					ft_strccat(*line, save_my_buff, '\n');
					printf("%s\n", *line);
				//	printf("%s\n", save_my_buff);
					save_my_buff = remove_start(save_my_buff);
			//	printf("%s\n", save_my_buff);
					return (1);
				}
				else
				{
					ret = read(fd, buff, BUFF_SIZE);
					ft_strccat(save_my_buff, buff, '\0');
				}
			}
			else
			{
				save_my_buff = ft_strdup(*line);
			}
		}
	return (0);
}

int	main(int ac, char **av)
{
	char *str;

	str = ft_memalloc(100000);
	if (ac > 2)
	{
		int i = -1;
		int fd = open(av[1], O_RDONLY);
		while (++i < ft_atoi(av[2]))
		{
			get_next_line(fd, &str);
//			printf("%s\n", str);
		}
	}
}

