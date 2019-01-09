/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:54:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/09 17:12:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
	
void	do_check(t_push *a, t_push *b, char *instruction)
{
	if (!ft_strcmp(instruction, "sa"))
			swap(a);
	if (!ft_strcmp(instruction, "sb"))
			swap(b);
	if (!ft_strcmp(instruction, "ss"))
			swap_both(a, b);
	if (!ft_strcmp(instruction, "pa"))
			push(b, a);
	if (!ft_strcmp(instruction, "pb"))
			push(a, b);
	if (!ft_strcmp(instruction, "ra"))
			rotate(a);
	if (!ft_strcmp(instruction, "ra"))
			rotate(b);
	if (!ft_strcmp(instruction, "rr"))
			rotate_both(a, b);
	if (!ft_strcmp(instruction, "rra"))
			rev_rotate(a);
	if (!ft_strcmp(instruction, "rrb"))
			rev_rotate(b);
	if (!ft_strcmp(instruction, "rrr"))
			rev_rotate_both(a, b);
}
