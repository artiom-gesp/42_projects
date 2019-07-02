/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inst_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:22:44 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/23 20:22:45 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"

int	handle_inst(t_vm *vm, t_proc *p, t_op *op)
{
	--p->sleep;
	if (p->sleep == 1)
	{
		p->d.pc = (p->pc + 1) & 0xfff;
		if (op->encoded_type)
		{
			p->d.typecode = vm->mem[p->d.pc];
			p->d.pc = (p->d.pc + 1) & 0xfff;
		}
		if (!(get_args(vm, p, op)))
			return (0);
		vm->opt & OPT_DEBUG ? print_operations(vm, p, p->pc) : 0;
		op->func(vm, p, &p->d);
		p->pc = p->d.pc;
		p->d.op = NULL;
	}
	else if (p->sleep <= 0)
	{
		p->sleep = op->sleep;
		p->d.op = op;
	}
	return (1);
}
