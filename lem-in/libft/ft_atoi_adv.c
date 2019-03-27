/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_adv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:18:19 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/04 14:18:20 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_adv(const char **nbr)
{
	uintmax_t	nb;
	const char	*nbr_tmp;

	nbr_tmp = *nbr;
	nb = 0;
	if (*nbr_tmp <= '9' && *nbr_tmp > '0')
		while (*nbr_tmp && *nbr_tmp <= '9' && *nbr_tmp >= '0')
		{
			nb *= 10;
			nb += (*nbr_tmp - '0');
			nbr_tmp++;
		}
	*nbr = nbr_tmp;
	return (nb);
}
