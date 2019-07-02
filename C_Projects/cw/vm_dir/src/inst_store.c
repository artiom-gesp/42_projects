/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:25:32 by agesp             #+#    #+#             */
/*   Updated: 2019/05/26 15:25:56 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st_32(t_vm *vm, t_proc *p, t_data *d)
{
	if ((d->typecode >> 4 & 0x03) == T_REG)
		p->r[d->args[1]] = d->args[0];
	else
		write_32(d->args[0], vm, p->pc + (int16_t)d->args[1] % IDX_MOD,
				p->player);
	return (1);
}

int		sti_32(t_vm *vm, t_proc *p, t_data *d)
{
	write_32(d->args[0], vm,
			p->pc + (int16_t)(d->args[1] + d->args[2]) % IDX_MOD, p->player);
	return (1);
}
