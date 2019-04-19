/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_attr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:31:23 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

int		init_attr(t_parsing **lst, const char *stack)
{
	if (*stack == '#' || *stack == '-' || *stack == '+'
	|| *stack == ' ' || *stack == '\'' || *stack == '0')
		(*lst)->attr = 1;
	else
		return (0);
	if (*stack == '#')
		(*lst)->hash = 1;
	else if (*stack == '-')
	{
		(*lst)->zero = 0;
		(*lst)->min = 1;
	}
	else if (*stack == '0' && (*lst)->min == 0)
		(*lst)->zero = 1;
	else if (*stack == '+')
	{
		(*lst)->max = 1;
		(*lst)->space = 0;
	}
	else if (*stack == ' ' && (*lst)->max == 0)
		(*lst)->space = 1;
	else if (*stack == '\'')
		(*lst)->cotes = 1;
	return (1);
}
