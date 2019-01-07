/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moment.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:04:33 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 14:45:03 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		nbr_len(int nbr)
{
	int ret;

	ret = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		ret++;
	}
	return (ret);
}

char	*ft_itoa(int nbr)
{
	int		i;
	int		len;
	char	*ret;

	len = nbr_len(nbr);
	i = 0;
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len] = '\0';
	len--;
	while (len >= 0)
	{
		ret[len] = nbr % 10 + 48;
		nbr /= 10;
		len--;
	}
	return (ret);
}

char	*moment(unsigned int duration)
{
	if (duration < 60)
		return (ft_itoa(duration));
	else if (duration < 3600)
		return (ft_itoa((int)(duration / 60)));
	else if (duration < 86400)
		return (ft_itoa((int)(duration / 3600)));
	else if (duration < 2592000)
		return (ft_itoa((int)((duration / 24) / 3600)));
	else
		return (ft_itoa((int)(((duration / 12) / 24) / 3600)));
}
