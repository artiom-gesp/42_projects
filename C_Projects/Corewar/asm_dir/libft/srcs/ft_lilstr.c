/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:03:11 by amanuel           #+#    #+#             */
/*   Updated: 2018/10/05 08:30:09 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_lilstr(char a, char b, char c)
{
	char		*s;

	s = NULL;
	if (!(s = malloc(4)))
	{
		write(1, "Erreur malloc ft_lilstr\n", 24);
		exit(-1);
	}
	s[0] = a;
	s[1] = b;
	s[2] = c;
	s[3] = 0;
	return (s);
}
