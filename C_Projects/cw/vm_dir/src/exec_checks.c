/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:40:24 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/24 12:40:26 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Kills the processes that didn't execute any live instruction
** during the last period, and resets the live counts of the other ones.
*/

static int	check_processes(t_vm *vm)
{
	int			total_live;
	t_proc		*cur;
	t_proc		*prev;

	total_live = 0;
	cur = vm->proc;
	prev = NULL;
	while (cur)
	{
		if (cur->lives > 0)
		{
			total_live += cur->lives;
			cur->lives = 0;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			kill_proc(vm, cur, prev);
			cur = prev ? prev->next : vm->proc;
		}
	}
	return (total_live);
}

/*
** This function is called every [cycle_to_die] cycles and
** performs various checks and adjustments:
**
** Dead processes are removed from the list.
** If the number of executions of the live instruction is above NBR_LIVE
** OR cycle to die hasn't been decreased since MAX CHECKS number of checks,
** then we decrement cycle_to_die by CYCLE_DELTA.
*/

int			periodic_check(t_vm *vm, int cycle_to_die)
{
	static int	nb_checks = 0;
	int			total_live;
	t_champ		*tmp;

	if (vm->opt & OPT_DEBUG)
		ft_dprintf(2, "cycle_to_die %d\n", cycle_to_die);
	total_live = check_processes(vm);
	++nb_checks;
	tmp = vm->champs;
	if (total_live >= NBR_LIVE || nb_checks == MAX_CHECKS)
	{
		cycle_to_die = cycle_to_die > CYCLE_DELTA
			? cycle_to_die - CYCLE_DELTA : 1;
		nb_checks = 0;
	}
	while (tmp)
	{
		tmp->nb_lives = 0;
		tmp = tmp->next;
	}
	return (cycle_to_die);
}
