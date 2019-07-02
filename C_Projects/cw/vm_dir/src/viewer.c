/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:26:10 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/16 18:26:12 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_arena_viewer(WINDOW *win, t_champ *ch)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		wprintmem(win, 0, i);
		++i;
	}
	while (ch)
	{
		i = 0;
		wattron(win, COLOR_PAIR(ch->play_pos));
		while (i < ch->size)
		{
			wprintmem(win, ch->code[i], i + ch->pc);
			++i;
		}
		wattroff(win, COLOR_PAIR(ch->play_pos));
		ch = ch->next;
	}
	wrefresh(win);
}

void		update_pc(WINDOW *win, t_proc *p)
{
	int		y;
	int		x;

	if (p->last_pc != p->pc)
	{
		y = p->last_pc / BPL + 1;
		x = (p->last_pc % BPL) * 3 + 1;
		mvwchgat(win, y, x, 2, A_NORMAL, p->last_color, NULL);
		y = p->pc / BPL + 1;
		x = (p->pc % BPL) * 3 + 1;
		p->last_color = PAIR_NUMBER(mvwinch(win, y, x) & A_ATTRIBUTES);
		mvwchgat(win, y, x, 2, A_REVERSE, p->player, NULL);
		p->last_pc = p->pc;
	}
}

int			update_viewer(t_vm *vm, int *cycles)
{
	update_info(vm, cycles);
	usleep(vm->vw->delay);
	wrefresh(vm->vw->mem_win);
	return (viewer_control(vm->vw));
}

void		display_winner(t_vm *vm)
{
	t_champ	*ch;

	ch = vm->champs;
	while (ch && ch->play_pos != vm->last_alive)
		ch = ch->next;
	if (ch)
	{
		mvwprintw(vm->vw->info_win, WIN_OFFSET, INFO_OFFSET,
			"And the winner is...");
		mvwprintw(vm->vw->info_win, WIN_OFFSET + 1, INFO_OFFSET,
			"player %d:", ch->player);
		wattron(vm->vw->info_win, COLOR_PAIR(ch->play_pos));
		mvwprintw(vm->vw->info_win, WIN_OFFSET + 1, INFO_OFFSET + 10,
			"%s !", ch->name);
		wattroff(vm->vw->info_win, COLOR_PAIR(ch->play_pos));
	}
	else
		mvwprintw(vm->vw->info_win, WIN_OFFSET, INFO_OFFSET,
			"Every champion sucked and nobody won");
}

void		viewer_aff(WINDOW *win, char c, int player)
{
	static int	x = INFO_OFFSET;
	static int	y = WIN_OFFSET;

	if (x > INFO_W - INFO_OFFSET)
	{
		++y;
		x = INFO_OFFSET;
	}
	mvwaddch(win, y, x, c | COLOR_PAIR(player));
	++x;
}
