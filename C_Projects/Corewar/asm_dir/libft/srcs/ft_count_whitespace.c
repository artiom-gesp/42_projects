/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 04:56:39 by amanuel           #+#    #+#             */
/*   Updated: 2018/10/01 15:12:36 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_count_whitespace(char *s)
{
	char			*initial;

	initial = s;
	if (s)
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
	return (s - initial);
}
