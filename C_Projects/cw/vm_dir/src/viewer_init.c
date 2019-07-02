/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:27:23 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/23 20:27:24 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_colors(void)
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(DEF_COLOR, COLOR_WHITE, COLOR_BLACK);
}

static int		init_windows(t_viewer *vw)
{
	if (!(vw->background = new_window((int[4]){BG_H, BG_W, BG_Y, BG_X},
		1, " ** COREWAR ** ")))
		return (1);
	if (!(vw->mem_win = new_window((int[4]){MEM_H, MEM_W, MEM_Y, MEM_X},
		0, " ARENA ")))
		return (2);
	if (!(vw->info_win = new_window((int[4]){INFO_H, INFO_W, INFO_Y, INFO_X},
		0, " INFOS ")))
		return (3);
	return (0);
}

int				size_check(void)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	getmaxyx(stdscr, y, x);
	return (y < BG_H || x < BG_W);
}

static void		*init_error(t_viewer *vw, char *msg)
{
	exit_viewer(vw, EXIT_FAILURE, msg);
	return (NULL);
}

t_viewer		*init_viewer(char *path)
{
	t_viewer	*vw;

	if (!(vw = ft_memalloc(sizeof(t_viewer))))
		return (init_error(vw, "alloc error (t_viewer)"));
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	init_colors();
	refresh();
	viewer_splash(path);
	nodelay(stdscr, TRUE);
	if (size_check())
		return (init_error(vw, "terminal window too small for viewer"));
	if (init_windows(vw))
		return (init_error(vw, "failed to initialize windows"));
	return (vw);
}
