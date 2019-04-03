/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:42:37 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

t_parsing	*init_prec(t_parsing *lst, const char **stack)
{
	const char *tmp_stack;

	tmp_stack = *stack;
	if (*tmp_stack == '.')
	{
		tmp_stack++;
		if (*tmp_stack == '*')
			lst->prec = -2;
		else if (!(lst->prec = ft_atoi_adv(&tmp_stack)))
			lst->prec = -1;
	}
	if (*tmp_stack == '0')
		tmp_stack++;
	*stack = tmp_stack;
	return (lst);
}
