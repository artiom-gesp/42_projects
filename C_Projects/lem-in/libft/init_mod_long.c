/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mod_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:31:48 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

const char	*init_mod_long(t_parsing **lst, const char *stack)
{
	if (*stack == 'h' || *stack == 'l' || *stack == 'j'
	|| *stack == 'z')
	{
		(*lst)->mod_long = 1;
		if (*stack == 'h' && *(stack + 1) == 'h')
		{
			(*lst)->hh = 1;
			stack++;
		}
		else if (*stack == 'h')
			(*lst)->h = 1;
		if (*stack == 'l' && *(stack + 1) == 'l')
		{
			(*lst)->ll = 1;
			stack++;
		}
		else if (*stack == 'l')
			(*lst)->l = 1;
		if (*stack == 'j')
			(*lst)->j = 1;
		if (*stack == 'z')
			(*lst)->z = 1;
		stack++;
	}
	return (stack);
}

int			initialiser_mod_long(t_parsing **lst, const char **stack)
{
	const char	mod[5] = "hljz";
	const char	*tmp_stack;
	int			i;
	t_parsing	*ptr;

	ptr = *lst;
	i = 0;
	tmp_stack = *stack;
	while (i < 5)
	{
		if (mod[i] == *tmp_stack)
		{
			*stack = init_mod_long(&ptr, tmp_stack);
			*lst = ptr;
			return (1);
		}
		i++;
	}
	return (0);
}
