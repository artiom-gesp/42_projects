/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:01:20 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/20 15:42:25 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	load_champ(t_vm *vm, t_champ *ch)
{
	int				i;
	int				j;
	int				pc;

	pc = (MEM_SIZE / vm->nb_players) * (ch->play_pos - 1);
	i = pc;
	j = 0;
	while (j < ch->size)
	{
		vm->mem[i] = ch->code[j];
		++i;
		++j;
	}
	return (pc);
}

static int	init_arena(t_vm *vm)
{
	t_champ	*tmp;
	uint8_t	play_pos;

	tmp = vm->champs;
	play_pos = 1;
	while (tmp)
	{
		tmp->play_pos = play_pos;
		tmp->pc = load_champ(vm, tmp);
		if (!(new_proc(vm, (t_proc){{play_pos, 0}, tmp->pc, tmp->pc,
							tmp->play_pos, 0, play_pos, 0, -1, 0,
							(t_data){{0}, 0, 0, NULL}, NULL})))
			return (0);
		tmp = tmp->next;
		++play_pos;
	}
	return (1);
}

static int	return_error(char *msg)
{
	if (msg)
		ft_dprintf(2, "%s\n", msg);
	return (0);
}

static void	introduce_contestants(t_vm *vm)
{
	t_champ	*tmp;

	tmp = vm->champs;
	ft_printf("Introducing contestants:\n");
	while (tmp)
	{
		ft_printf("player %d : \e[3%dm%s\e[0m\n", tmp->player,
			tmp->play_pos, tmp->name);
		if (vm->opt & OPT_DESC)
			ft_printf("%s\n", tmp->comment);
		tmp = tmp->next;
	}
}

int			init_vm(t_vm *vm, char *path)
{
	if (REG_SIZE != 4)
		return (return_error("invalid register size"));
	if (vm->nb_players > MAX_PLAYERS || vm->nb_players < 0)
		return (return_error("incorrect number of players"));
	if (!(init_arena(vm)))
		return (return_error("failed to load champions in arena"));
	if (vm->opt & OPT_VIEWER && !(vm->vw = init_viewer(path)))
		return (0);
	if (vm->opt & OPT_VIEWER)
	{
		init_arena_viewer(vm->vw->mem_win, vm->champs);
		init_info_viewer(vm->vw->info_win, vm->champs);
	}
	else
		introduce_contestants(vm);
	return (1);
}
