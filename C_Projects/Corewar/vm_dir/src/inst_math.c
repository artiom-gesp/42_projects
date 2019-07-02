/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_inst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:23:49 by agesp             #+#    #+#             */
/*   Updated: 2019/05/26 15:24:49 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[2]] = d->args[0] + d->args[1];
	p->carry = (p->r[d->args[2]] == 0);
	return (1);
}

int		sub_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[2]] = d->args[0] - d->args[1];
	p->carry = (p->r[d->args[2]] == 0);
	return (1);
}

int		and_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[2]] = d->args[0] & d->args[1];
	p->carry = (p->r[d->args[2]] == 0);
	return (1);
}

int		or_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[2]] = d->args[0] | d->args[1];
	p->carry = (p->r[d->args[2]] == 0);
	return (1);
}

int		xor_32(t_vm *vm, t_proc *p, t_data *d)
{
	(void)vm;
	p->r[d->args[2]] = d->args[0] ^ d->args[1];
	p->carry = (p->r[d->args[2]] == 0);
	return (1);
}
