/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_splash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:30:01 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/23 20:30:02 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_xy(int fd, int *x, int *y)
{
	char	c;

	c = 1;
	*x = 0;
	*y = 0;
	while ((c && c != '\n'))
	{
		if (read(fd, &c, 1) <= 0)
			return (0);
		++*x;
	}
	*y = lseek(fd, 0, SEEK_END) / *x;
	lseek(fd, 0, SEEK_SET);
	*x = (BG_W - *x) / 2;
	*y = (BG_H - *y) / 2;
	return (1);
}

static int	display(int fd, int x, int y)
{
	int		i;
	int		j;
	char	c;

	i = x;
	j = y;
	c = 1;
	while (c != 0)
	{
		if (read(fd, &c, 1) <= 0)
			return (1);
		if (c == '\n')
		{
			i = x;
			++j;
		}
		else
		{
			mvprintw(j, i, "%c", c);
			usleep(40000 / x);
			refresh();
			++i;
		}
	}
	return (1);
}

static int	exit_splash(int fd, int exit_status)
{
	if (fd >= 0)
		close(fd);
	if (exit_status == 1)
		getch();
	return (exit_status);
}

/*
** extracts the directory part out of a binary path
*/

static char	*get_path(char *path)
{
	char	*splash_path;
	size_t	path_len;
	int		i;

	path_len = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			path_len = i;
		++i;
	}
	splash_path = ft_strndup(path, path_len + 1);
	return (ft_strjoin_f(splash_path, SPLASH_FILE, 1));
}

int			viewer_splash(char *path)
{
	int		fd;
	int		x;
	int		y;
	char	*splash_path;

	if (!(splash_path = get_path(path)))
		return (0);
	if ((fd = open(splash_path, O_RDONLY)) < 0)
		return (exit_splash(fd, 0));
	free(splash_path);
	if (!get_xy(fd, &x, &y))
		return (exit_splash(fd, 0));
	if (x > BG_W || y > BG_H)
		return (exit_splash(fd, 0));
	if (!(display(fd, x, y)))
		return (exit_splash(fd, 0));
	return (exit_splash(fd, 1));
}
