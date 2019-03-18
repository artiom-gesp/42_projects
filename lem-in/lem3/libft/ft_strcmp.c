/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:24:43 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:24:44 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*ucs1;
	unsigned char	*ucs2;

	i = 0;
	ucs1 = (unsigned char *)s1;
	ucs2 = (unsigned char *)s2;
	while (ucs1[i] != '\0' || ucs2[i] != '\0')
	{
		if (ucs1[i] > ucs2[i] || ucs1[i] < ucs2[i])
			return (ucs1[i] - ucs2[i]);
		i++;
	}
	return (0);
}
