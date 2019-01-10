/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:02:05 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 14:47:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static unsigned int	ft_linelen(char *mem)
{
	unsigned int	i;

	i = 0;
	while (mem[i] != '\n' && mem[i] != '\0')
		i++;
	return (i);
}

static char			*ft_chrcpy(char *mem)
{
	if (ft_strchr(mem, '\n'))
	{
		ft_strcpy(mem, ft_strchr(mem, '\n') + 1);
		return (mem);
	}
	if (ft_linelen(mem) > 0)
	{
		ft_strcpy(mem, ft_strchr(mem, '\0'));
		return (mem);
	}
	return (NULL);
}

int					get_next_line(int const fd, char **line)
{
	static char		*mem[4863];
	char			buff[BUFF_SIZE + 1];
	char			*sline;
	int				sread;

	if (BUFF_SIZE < 1 || fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(mem[fd]) && (mem[fd] = ft_strnew(0)) == NULL)
		return (-1);
	while (!(ft_strchr(mem[fd], '\n')) &&
			(sread = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[sread] = '\0';
		sline = mem[fd];
		mem[fd] = ft_strjoin(sline, buff);
		free(sline);
	}
	*line = ft_strsub(mem[fd], 0, ft_linelen(mem[fd]));
	if (ft_chrcpy(mem[fd]) == NULL)
	{
		free(mem[fd]);
		return (0);
	}
	return (1);
}
