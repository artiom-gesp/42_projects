/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_inst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:22:20 by agesp             #+#    #+#             */
/*   Updated: 2019/06/20 17:16:43 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ld_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[1]] = (int32_t)d->args[0];
	p->carry = (d->args[0] == 0);
	return (1);
}

int		ldi_32(t_vm *vm, t_proc *p, t_data *d)
{
	int16_t x;

	x = ((int16_t)(d->args[0] + d->args[1]) % IDX_MOD + p->pc) & 0xfff;
	p->r[d->args[2]] = read_32(vm->mem, x);
	return (1);
}

int		lld_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[1]] = d->args[0];
	p->carry = (d->args[0] == 0);
	return (1);
}

int		lldi_32(t_vm *vm, t_proc *p, t_data *d)
{
	int	reg;

	reg = d->args[2];
	if (reg >= 0 && reg < REG_NUMBER)
	{
		p->r[d->args[2]] = vm->mem[(d->args[0] + d->args[1]) & 0xfff];
		p->carry = (p->r[d->args[2]] == 0);
	}
	return (1);
}
