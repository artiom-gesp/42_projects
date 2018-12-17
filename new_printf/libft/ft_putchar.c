/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:25:40 by agesp             #+#    #+#             */
/*   Updated: 2018/12/17 14:53:14 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putchar(int c)
{
	char	*save;
	char	*ret;
	char	*retun;
	char	*retdeux;
	char	*rettrois;
	int		digit;

	
	ret = get_bits(c);
	printf("%s\n", ret);
	/*if (!(save = malloc(sizeof(char) * 4)))
		return ;
	if (ft_strlen(ret) > 8)
	{
		retun = ret;
		ft_strncpy(save, ret, 4);
		printf("%s\n" ,save);
		digit = ft_atoi_base(save, 2);
		ret = ft_strjoin("1110", ft_itoa_base(digit, 16, 'a'));
		printf("%s\n", ret);
	//	write(1, &c, 1);
	}*/
}

int	main()
{
	ft_putchar(4660);
}
