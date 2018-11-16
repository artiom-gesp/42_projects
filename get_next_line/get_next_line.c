/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:11:04 by agesp             #+#    #+#             */
/*   Updated: 2018/11/16 17:21:22 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int ft_strccat(char *dst, const char* src, int c)
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

char	*ft_strccpy(char *dst, const char *src, int c)
{
	int i;

	i = 0;
	while (src[i])
	{
		if (src[i] == c)
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

char *remove_start(char *save_my_buff)
{
	int i;

	i = 0;
	while (save_my_buff[i] && save_my_buff[i] != '\n')
		i++;
		return (char*)&save_my_buff[i + 1];
}

char	*ft_strcdup(char const *s, int c)
{
	char	*dst;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(dst = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (s[i] != c)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int		get_next_line(int const fd, char **line)
{
	int ret;
	char buff[BUFF_SIZE + 1];
	static char *save_my_buff;
	ret = 1;
	while (ret > 0)
	{
			if (save_my_buff)
			{
				if (ft_strchr(save_my_buff, '\n'))
				{
					*line = ft_strccpy(save_my_buff, save_my_buff, '\n');
					save_my_buff = remove_start(save_my_buff);
					return (1);
				}
				else
				{
					ret = read(fd, buff, BUFF_SIZE);
					buff[ret] = '\0';
					ft_strccat(save_my_buff, buff, '\0');
				}
			}
			else
			{
				save_my_buff = ft_memalloc(sizeof(buff));
			}
	}
	return (0);
}

int	main(int ac, char **av)
{/*
	char *str;

//	str = ft_memalloc(1111111);
	if (ac > 2)
	{
		int i = -1;
		int fd = open(av[1], O_RDONLY);
		while (++i < ft_atoi(av[2]))
		{
			get_next_line(fd, &str);
			printf("%s\n", str);
		}
	}
*/
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	int			errors;

	fd = open("test", O_RDONLY);
	count_lines = 0;
	errors = 0;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (count_lines == 0 && strcmp(line, "1234567") != 0)
			errors++;
		if (count_lines == 1 && strcmp(line, "abcdefg") != 0)
			errors++;
		if (count_lines == 2 && strcmp(line, "4567890") != 0)
			errors++;
		if (count_lines == 3 && strcmp(line, "defghij") != 0)
			errors++;
		count_lines++;
		if (count_lines > 50)
			break ;
//		printf("%d\n", errors);
	}
	printf("%d\n", count_lines);
}
