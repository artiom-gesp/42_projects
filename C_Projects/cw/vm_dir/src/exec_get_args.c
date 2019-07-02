/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:07:35 by agesp             #+#    #+#             */
/*   Updated: 2019/05/26 15:08:52 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Returns the type of the expected argument, based on the encoding octet
** that follows the opcode.
*/

static t_arg_type		get_type(uint8_t code, int arg_nb)
{
	static int	type_table[4] = {T_ERR, T_REG, T_DIR, T_IND};

	if (arg_nb == 0)
		code = (code >> 6) & 0x3;
	else if (arg_nb == 1)
		code = (code >> 4) & 0x3;
	else if (arg_nb == 2)
		code = (code >> 2) & 0x3;
	else
		return (T_ERR);
	return (type_table[code]);
}

static inline uint32_t	get_reg(t_vm *vm, t_proc *p, int pos, t_op *op)
{
	uint32_t	arg;

	if (pos + 1 == op->nb_arg && op->opcode != 0x0b)
		arg = vm->mem[p->d.pc] - 1;
	else
		arg = p->r[vm->mem[p->d.pc] - 1];
	p->d.pc = (p->d.pc + REG_OFFSET) & 0xfff;
	return (arg);
}

static inline uint32_t	get_ind(t_vm *vm, t_proc *p, t_op *op)
{
	int16_t		offset;
	uint32_t	arg;

	offset = read_16(vm->mem, p->d.pc);
	if (op->opcode == 0x03)
		arg = read_16(vm->mem, p->d.pc);
	else
	{
		if (op->mod)
			offset %= IDX_MOD;
		arg = read_32(vm->mem, p->pc + offset);
	}
	p->d.pc = (p->d.pc + IND_OFFSET) & 0xfff;
	return (arg);
}

static inline uint32_t	get_dir(t_vm *vm, t_proc *p, t_op *op)
{
	uint32_t	arg;

	(void)p;
	if (op->alt_dir_size)
	{
		arg = (uint32_t)read_16(vm->mem, p->d.pc);
		p->d.pc = (p->d.pc + DIR_OFFSET / 2) & 0xfff;
	}
	else
	{
		arg = read_32(vm->mem, p->d.pc);
		p->d.pc = (p->d.pc + DIR_OFFSET) & 0xfff;
	}
	return (arg);
}

/*
** Gets all the arguments and stores them in an array.
** Returns 0 if the type of an argument is invalid for a specific instruction,
** 1 otherwise.
*/

int						get_args(t_vm *vm, t_proc *p, t_op *op)
{
	t_arg_type	type;
	int			i;

	i = 0;
	while (i < op->nb_arg)
	{
		if (!((type = get_type(p->d.typecode, i)) & op->allowed_types[i])
				&& p->d.op->encoded_type)
			return (0);
		if (!p->d.op->encoded_type)
			type = 0;
		if (type & T_REG)
		{
			if (vm->mem[p->d.pc] > REG_NUMBER || vm->mem[p->d.pc] <= 0)
				return (0);
			p->d.args[i] = get_reg(vm, p, i, op);
		}
		else if (type & T_IND)
			p->d.args[i] = get_ind(vm, p, op);
		else
			p->d.args[i] = get_dir(vm, p, op);
		++i;
	}
	return (1);
}
