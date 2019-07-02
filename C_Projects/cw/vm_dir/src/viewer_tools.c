/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:28:31 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/23 20:28:32 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "viewer.h"
#include "libft.h"
#include "ft_printf.h"

void	wprintmem(WINDOW *win, uint8_t val, int pc)
{
	mvwprintw(win, pc / BPL + 1, (pc % BPL) * 3 + 1, "%.2x", val);
}

void	wprintmemc_32(WINDOW *win, uint32_t val, int pc, int player)
{
	wattron(win, COLOR_PAIR(player));
	wprintmem(win, val >> 24, pc);
	wprintmem(win, val >> 16, pc + 1);
	wprintmem(win, val >> 8, pc + 2);
	wprintmem(win, val, pc + 3);
	wattron(win, COLOR_PAIR(DEF_COLOR));
}

void	wprintmemc(WINDOW *win, uint8_t val, int pc, int color)
{
	attron(COLOR_PAIR(color));
	mvwprintw(win, pc / BPL + 1, (pc % BPL) * 3 + 1, "%.2x", val);
	attroff(COLOR_PAIR(color));
}

int		exit_viewer(t_viewer *vw, int exit_status, char *msg)
{
	if (vw)
	{
		if (vw->background)
			delwin(vw->background);
		if (vw->mem_win)
			delwin(vw->mem_win);
		if (vw->info_win)
			delwin(vw->info_win);
		curs_set(1);
		delwin(stdscr);
		endwin();
		free(vw);
	}
	if (msg)
		exit_status == EXIT_SUCCESS
			? ft_printf("viewer: %s\n", msg)
			: ft_dprintf(2, "viewer: %s\n", msg);
	return (exit_status);
}

WINDOW	*new_window(int x[4], int border, char *title)
{
	WINDOW	*win;

	if (!(win = newwin(x[0], x[1], x[2], x[3])))
		return (NULL);
	if (border == 1)
		box(win, 0, 0);
	if (title)
		mvwprintw(win, 0, (x[1] - ft_strlen(title)) / 2, "%s", title);
	if (wrefresh(win) == ERR)
		return (NULL);
	return (win);
}
