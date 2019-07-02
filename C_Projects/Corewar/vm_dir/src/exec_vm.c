/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:08:54 by agesp             #+#    #+#             */
/*   Updated: 2019/06/20 17:39:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"

static int	g_max_offset[16] = {5, 7, 5, 5, 5, 9, 9, 9, 3, 7, 7, 3, 7, 7, 3, 3};

/*
** reads the memory cell pointed at by the pc of the current process.
** If it's an opcode for an instruction, appropriate actions are taken:
** Else, pc is increased to point at the next cell.
*/

static void	read_byte(t_vm *vm, t_proc *p)
{
	uint8_t		data;

	data = vm->mem[p->pc];
	if (0 < data && data <= 16)
	{
		if (p->d.op && p->d.op != &g_optab[data - 1])
		{
			p->sleep = 1;
			p->pc = (p->pc + g_max_offset[p->d.op->opcode - 1] + 1) & 0xfff;
			p->d.op = NULL;
			return ;
		}
		if (!(handle_inst(vm, p, &g_optab[data - 1])))
			p->pc = (p->pc + 1) & 0xfff;
	}
	else if (p->d.op)
	{
		p->sleep = 1;
		p->pc = (p->pc + (g_max_offset[p->d.op->opcode - 1] + 1)) & 0xfff;
		p->d.op = NULL;
	}
	else
		p->pc = (p->pc + 1) & 0xfff;
}

static int	exec_cycle(t_vm *vm, int current_cycle, int cycle_to_die)
{
	t_proc	*tmp;

	tmp = vm->proc;
	vm->nb_procs = 0;
	while (tmp)
	{
		read_byte(vm, tmp);
		if (vm->opt & OPT_VIEWER)
			update_pc(vm->vw->mem_win, tmp);
		tmp = tmp->next;
		++vm->nb_procs;
	}
	return (current_cycle == cycle_to_die ? 0 : current_cycle + 1);
}

static void	exec_done(t_vm *vm)
{
	if (vm->opt & OPT_VIEWER)
	{
		display_winner(vm);
		viewer_pause(vm->vw);
		exit_viewer(vm->vw, EXIT_SUCCESS, NULL);
	}
	else
		get_winner(vm);
}

/*
** Iterate among all the process while atleast one is alive
*/

void		exec_vm(t_vm *vm)
{
	int		cycle[3];

	cycle[C_CURR] = 1;
	cycle[C_TOTAL] = 1;
	cycle[C_DIE] = CYCLE_TO_DIE;
	if (vm->opt & OPT_VIEWER && !viewer_pause(vm->vw))
		return ((void)exit_viewer(vm->vw, EXIT_SUCCESS, NULL));
	while (vm->proc && cycle[C_DIE] > 0)
	{
		if ((cycle[C_CURR] = exec_cycle(vm, cycle[C_CURR], cycle[C_DIE])) == 0)
			cycle[C_DIE] = periodic_check(vm, cycle[C_DIE]);
		if (vm->opt & OPT_DEBUG)
			ft_dprintf(2, "CYCLE %d\n", cycle[C_TOTAL]);
		++cycle[C_TOTAL];
		if (vm->opt & OPT_VIEWER && !(update_viewer(vm, cycle)))
			return ((void)exit_viewer(vm->vw, EXIT_SUCCESS, NULL));
		if (cycle[C_TOTAL] == vm->dump && vm->dump > 0)
		{
			if (!(vm->opt & OPT_VIEWER))
				return (dump_vm(vm, 64));
			else if (!(viewer_pause(vm->vw)))
				return ((void)exit_viewer(vm->vw, EXIT_SUCCESS, NULL));
		}
	}
	exec_done(vm);
}
