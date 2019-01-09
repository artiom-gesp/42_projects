/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:54:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/09 18:51:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
	
int		do_check(t_push *a, t_push *b, char *instruction, int flag)
{
	if (!ft_strcmp(instruction, "sa"))
			swap(a);
	else if (!ft_strcmp(instruction, "sb"))
			swap(b);
	else if (!ft_strcmp(instruction, "ss"))
			swap_both(a, b);
	else if (!ft_strcmp(instruction, "pa"))
			push(b, a);
	else if (!ft_strcmp(instruction, "pb"))
			push(a, b);
	else if (!ft_strcmp(instruction, "ra"))
			rotate(a);
	else if (!ft_strcmp(instruction, "ra"))
			rotate(b);
	else if (!ft_strcmp(instruction, "rr"))
			rotate_both(a, b);
	else if (!ft_strcmp(instruction, "rra"))
			rev_rotate(a);
	else if (!ft_strcmp(instruction, "rrb"))
			rev_rotate(b);
	else if (!ft_strcmp(instruction, "rrr"))
			rev_rotate_both(a, b);
	else
		return (0);
	if (flag)
		print_plist(a, b);
	return (1);
}
