/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 23:16:01 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/16 23:16:03 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_players_info(WINDOW *win, t_champ *ch)
{
	int		i;

	i = 0;
	while (ch)
	{
		mvwprintw(win, i * 4 + 1, INFO_OFFSET, "player %d:", ch->player);
		wattron(win, COLOR_PAIR(ch->play_pos));
		mvwprintw(win, i * 4 + 1, INFO_OFFSET + 12, "%s", ch->name);
		wattron(win, COLOR_PAIR(DEF_COLOR));
		mvwprintw(win, i * 4 + 2, INFO_OFFSET, "lives:");
		mvwprintw(win, i * 4 + 3, INFO_OFFSET, "procs:");
		ch = ch->next;
		++i;
	}
}

void		init_info_viewer(WINDOW *win, t_champ *ch)
{
	init_players_info(win, ch);
	mvwprintw(win, STAT_OFFSET, INFO_OFFSET, "cycles:");
	mvwprintw(win, STAT_OFFSET, COLUMN_OFFSET, "current\ttotal\t\tto_die");
	mvwprintw(win, STAT_OFFSET + 1, COLUMN_OFFSET, "0\t\t0\t\t0");
	mvwprintw(win, STAT_OFFSET + 3, INFO_OFFSET, "current status:");
	mvwprintw(win, STAT_OFFSET + 3, COLUMN_OFFSET, "paused");
	mvwprintw(win, STAT_OFFSET + 4, INFO_OFFSET, "delay:");
	mvwprintw(win, STAT_OFFSET + 4, COLUMN_OFFSET, "0");
	mvwprintw(win, STAT_OFFSET + 5, INFO_OFFSET, "procs alive:");
	mvwprintw(win, STAT_OFFSET + 5, COLUMN_OFFSET, "0");
	mvwprintw(win, CONTROL_OFFSET, INFO_OFFSET, "controls:");
	mvwprintw(win, CONTROL_OFFSET + 1, INFO_OFFSET, "pause/run:");
	mvwprintw(win, CONTROL_OFFSET + 1, COLUMN_OFFSET, "space");
	mvwprintw(win, CONTROL_OFFSET + 2, INFO_OFFSET, "quit:");
	mvwprintw(win, CONTROL_OFFSET + 2, COLUMN_OFFSET, "q");
	mvwprintw(win, CONTROL_OFFSET + 3, INFO_OFFSET, "speed modes:");
	mvwprintw(win, CONTROL_OFFSET + 3, COLUMN_OFFSET, "1/2/3");
	mvwprintw(win, CONTROL_OFFSET + 4, INFO_OFFSET, "faster/slower:");
	mvwprintw(win, CONTROL_OFFSET + 4, COLUMN_OFFSET, "d/e");
	wrefresh(win);
}

static void	update_player(WINDOW *win, t_champ *champs)
{
	int		i;

	i = 0;
	while (champs)
	{
		mvwprintw(win, i * 4 + 2, COLUMN_OFFSET, "%d\t\t", champs->nb_lives);
		mvwprintw(win, i * 4 + 3, COLUMN_OFFSET, "%d\t\t", champs->nb_procs);
		++i;
		champs = champs->next;
	}
}

static void	update_stats(WINDOW *win, int *cycles, int nb_procs)
{
	mvwprintw(win, STAT_OFFSET + 1, COLUMN_OFFSET, "%d\t\t%d\t\t%d\t",
		cycles[C_CURR], cycles[C_TOTAL], cycles[C_DIE]);
	mvwprintw(win, STAT_OFFSET + 5, COLUMN_OFFSET, "%d\t\t", nb_procs);
}

void		update_info(t_vm *vm, int *cycles)
{
	update_player(vm->vw->info_win, vm->champs);
	update_stats(vm->vw->info_win, cycles, vm->nb_procs);
	wrefresh(vm->vw->info_win);
}
