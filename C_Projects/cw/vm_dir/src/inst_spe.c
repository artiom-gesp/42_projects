/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 13:52:31 by agesp             #+#    #+#             */
/*   Updated: 2019/06/20 15:44:00 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		live_32(t_vm *vm, t_proc *p, t_data *d)
{
	t_champ	*tmp;
	int		data;

	tmp = vm->champs;
	++p->lives;
	data = (int)d->args[0];
	while (tmp)
	{
		if (tmp->play_pos == data)
		{
			vm->last_alive = data;
			++tmp->nb_lives;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		zjmp_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	if (p->carry == 1)
	{
		d->pc = (p->pc + ((int16_t)d->args[0] % IDX_MOD)) & 0xfff;
		return (1);
	}
	return (0);
}

int		fork_32(t_vm *vm, t_proc *p, t_data *d)
{
	t_proc	*n;

	if (!(n = new_proc(vm, *p)))
		return (0);
	n->pc = (p->pc + (int16_t)d->args[0] % IDX_MOD) & 0xfff;
	n->d.op = NULL;
	return (1);
}

int		lfork_32(t_vm *vm, t_proc *p, t_data *d)
{
	t_proc	*n;

	if (!(n = new_proc(vm, *p)))
		return (0);
	n->pc = (p->pc + d->args[0]) & 0xfff;
	return (1);
}

int		aff_32(t_vm *vm, t_proc *p, t_data *d)
{
	char	c;

	(void)vm;
	c = p->r[d->args[0]] % IDX_MOD;
	if (vm->opt & OPT_VIEWER)
		viewer_aff(vm->vw->info_win, c, p->player);
	else
		ft_printf("%c", c);
	return (1);
}
