/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 10:44:25 by agesp             #+#    #+#             */
/*   Updated: 2019/06/20 15:44:31 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_winner(t_vm *vm)
{
	t_champ *tmp;

	tmp = vm->champs;
	while (tmp && tmp->play_pos != vm->last_alive)
		tmp = tmp->next;
	if (!tmp)
		ft_printf("It's a draw ! No player were reported as alive\n");
	else
		ft_printf("Contestant %d, \e[3%dm%s\e[0m won the game !\n",
				tmp->player, tmp->play_pos, tmp->name);
}

void	dump_vm(t_vm *vm, int octet_per_line)
{
	int i;

	i = 1;
	while (i <= MEM_SIZE)
	{
		vm->mem[i - 1] != 0 ? ft_printf("%02x", vm->mem[i - 1])
			: ft_printf("%{red}%02x%{eoc}", vm->mem[i - 1]);
		(i % (octet_per_line) == 0 && i != 0) ? ft_printf("\n")
			: ft_printf(" ");
		++i;
	}
}
