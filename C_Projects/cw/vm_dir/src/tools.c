/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:57:48 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/20 15:02:02 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Only works for memory area of size 4096 (0x1000) and 32 bits registers
*/

/*
** Reads 16 bits of data from a circular memory area and returns it
** as an signed int of 16 bits
*/

int16_t				read_16(void *data, int idx)
{
	uint8_t		tmp[2];
	uint8_t		*d;

	d = data;
	tmp[1] = d[idx];
	tmp[0] = d[(idx + 1) & 0xfff];
	return (*(int16_t*)tmp);
}

/*
** Reads 32 bits of data from a circular memory area and returns it
** as an unsigned int of 32 bits
*/

uint32_t			read_32(void *data, int idx)
{
	uint8_t	ret[4];
	uint8_t	*d;

	d = data;
	ret[3] = d[(idx + 0) & 0xfff];
	ret[2] = d[(idx + 1) & 0xfff];
	ret[1] = d[(idx + 2) & 0xfff];
	ret[0] = d[(idx + 3) & 0xfff];
	return (*(uint32_t*)ret);
}

/*
** Writes a 4 bytes unsigned int into memory.
*/

void				write_32(uint32_t data, t_vm *vm, int i, int player)
{
	uint8_t	*to;

	to = vm->mem;
	to[(i + 3) & 0xfff] = data;
	to[(i + 2) & 0xfff] = data >> 8;
	to[(i + 1) & 0xfff] = data >> 16;
	to[(i + 0) & 0xfff] = data >> 24;
	if (vm->opt & OPT_VIEWER)
	{
		wattron(vm->vw->mem_win, COLOR_PAIR(player));
		wprintmemc(vm->vw->mem_win, to[(i + 0) & 0xfff],
			(i + 0) & 0xfff, player);
		wprintmemc(vm->vw->mem_win, to[(i + 1) & 0xfff],
			(i + 1) & 0xfff, player);
		wprintmemc(vm->vw->mem_win, to[(i + 2) & 0xfff],
			(i + 2) & 0xfff, player);
		wprintmemc(vm->vw->mem_win, to[(i + 3) & 0xfff],
			(i + 3) & 0xfff, player);
		wattroff(vm->vw->mem_win, COLOR_PAIR(player));
	}
}

void				kill_proc(t_vm *vm, t_proc *cur, t_proc *prev)
{
	t_champ	*tmp;

	tmp = vm->champs;
	if (cur == vm->proc)
		vm->proc = cur->next;
	else
		prev->next = cur->next;
	if (vm->opt & OPT_VIEWER)
		mvwchgat(vm->vw->mem_win, cur->last_pc / BPL + 1,
			(cur->last_pc % BPL) * 3 + 1, 2, A_NORMAL, cur->last_color, NULL);
	while (tmp)
	{
		if (tmp->play_pos == cur->player)
			--tmp->nb_procs;
		tmp = tmp->next;
	}
	free(cur);
}

t_proc				*new_proc(t_vm *vm, t_proc p)
{
	t_proc		*new;
	static int	proc_pos = 0;
	t_champ		*tmp;

	tmp = vm->champs;
	if (!(new = malloc(sizeof(t_proc))))
	{
		ft_dprintf(2, "corewar: malloc error\n");
		return (NULL);
	}
	*new = p;
	new->sleep = 0;
	new->next = vm->proc;
	vm->proc = new;
	vm->proc->pos = ++proc_pos;
	while (tmp)
	{
		if (tmp->play_pos == p.player)
			++tmp->nb_procs;
		tmp = tmp->next;
	}
	return (new);
}
