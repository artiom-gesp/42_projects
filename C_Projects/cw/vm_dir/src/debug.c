/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:36:17 by agesp             #+#    #+#             */
/*   Updated: 2019/05/26 14:48:22 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"

/*
** returns 2 for dir, 3 for ind and 1 for reg
*/

void			regular_print(t_vm *vm, int type, int int_size, int *pc)
{
	if (type == 1)
	{
		ft_printf("r%d ", vm->mem[*pc]);
		*pc = (*pc + 1) & 0xfff;
	}
	else
	{
		if (int_size == 4 && type == 2)
		{
			ft_printf("%d ", read_32(vm->mem, *pc));
			*pc = (*pc + 4) & 0xfff;
		}
		else if (type == 3)
		{
			ft_printf("%d ",
				read_16(vm->mem, ((*pc - 2) + read_16(vm->mem, *pc)) & 0xfff));
			*pc = (*pc + 2) & 0xfff;
		}
		else
		{
			ft_printf("%d ", read_16(vm->mem, *pc));
			*pc = (*pc + 2) & 0xfff;
		}
	}
}

void			special_print(t_vm *vm, int pc, int carry)
{
	if (vm->mem[pc] == 0x01)
	{
		pc = (pc + 1) & 0xfff;
		ft_printf("%d ", read_32(vm->mem, pc));
		pc = (pc + 4) & 0xfff;
	}
	else
	{
		pc = (pc + 1) & 0xfff;
		ft_printf("%d ", read_16(vm->mem, pc));
		if (vm->mem[(pc - 1) & 0xfff] == 0x09 && carry)
			ft_printf("<- OK !");
		else if (vm->mem[(pc - 1) & 0xfff] == 0x09)
			ft_printf("<- FAIL !");
		pc = (pc + 2);
	}
}

void			init_var(t_vm *vm, int *pc, int *int_size, uint8_t *code)
{
	*int_size = (vm->mem[*pc] == 0x02 || (vm->mem[*pc] >= 0x06
				&& vm->mem[*pc] <= 0x08) || vm->mem[*pc] == 0x0d) ? 4 : 2;
	if (vm->mem[*pc] != 0x0f && vm->mem[*pc] != 0x0c
			&& vm->mem[*pc] != 0x09 && vm->mem[*pc] != 0x01)
	{
		*pc = (*pc + 1) & 0xfff;
		*code = vm->mem[*pc];
	}
	else
		*code = 0;
}

void			print_operations(t_vm *vm, t_proc *p, int pc)
{
	uint8_t	code;
	int		shift;
	int		int_size;

	shift = 6;
	ft_printf("PROC_%d : ", p->pos);
	if (0 < vm->mem[pc] && vm->mem[pc] <= 16)
		ft_printf("%s ", g_optab[vm->mem[pc] - 1].name);
	else
		ft_printf("fork ");
	init_var(vm, &pc, &int_size, &code);
	if (code)
	{
		pc = (pc + 1) & 0xfff;
		while (code >> shift & 0x03)
		{
			regular_print(vm, code >> shift & 0x03, int_size, &pc);
			shift -= 2;
		}
	}
	else
		special_print(vm, pc, p->carry);
	ft_printf("\nPC WENT FROM %#x TO %#x\n", p->pc, p->d.pc);
}
