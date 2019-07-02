/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 19:37:40 by pfragnou          #+#    #+#             */
/*   Updated: 2019/05/26 15:03:28 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	free_champs(t_champ *ch)
{
	t_champ	*tmp;

	while (ch)
	{
		tmp = ch->next;
		free(ch);
		ch = tmp;
	}
}

static void	free_proc(t_proc *p)
{
	t_proc	*tmp;

	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

static int	exit_vm(t_vm *vm, int exit_status, char *msg)
{
	if (msg)
		exit_status == EXIT_SUCCESS
			? ft_printf("corewar: %s\n", msg)
			: ft_dprintf(2, "corewar: %s\n", msg);
	if (vm->champs)
		free_champs(vm->champs);
	if (vm->proc)
		free_proc(vm->proc);
	return (exit_status);
}

static int	usage_vm(t_vm *vm)
{
	if (vm->opt & OPT_HELP)
	{
		ft_dprintf(2, "Corewar is a game in which champions battle in a ");
		ft_dprintf(2, "restricted memory area. The winner is the last one ");
		ft_dprintf(2, "standing. To achieve this, they have a limited set ");
		ft_dprintf(2, "of basic instructions at their disposal\n\n");
	}
	ft_dprintf(2, "usage:\t./corewar [-g/d/h/v/l/n] <.cor...>\n");
	ft_dprintf(2, "\t-h --help: help\n");
	ft_dprintf(2, "\t-g --debug: debug mode\n");
	ft_dprintf(2, "\t-v --viewer: graphic mode\n");
	ft_dprintf(2, "\t-d --dump X: stops the execution and dump the memory ");
	ft_dprintf(2, "after X cycles. Can be combined with -v to pause ");
	ft_dprintf(2, "the viewer after X cycles instead\n");
	ft_dprintf(2, "\t-n X <.cor>: assigns number X to the next champion\n");
	ft_dprintf(2, "\t-c: display champions comments\n");
	return (exit_vm(vm, vm->opt & OPT_HELP
		? EXIT_SUCCESS : EXIT_FAILURE, NULL));
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	vm = (t_vm){0, 0, 0, NULL, 0, {0}, 0, NULL, NULL};
	if (!parse_input(argc, argv, &vm) || vm.opt & OPT_HELP || vm.nb_players < 1)
		return (usage_vm(&vm));
	if (!init_vm(&vm, argv[0]))
		return (exit_vm(&vm, EXIT_FAILURE, NULL));
	exec_vm(&vm);
	return (exit_vm(&vm, EXIT_SUCCESS, NULL));
}
