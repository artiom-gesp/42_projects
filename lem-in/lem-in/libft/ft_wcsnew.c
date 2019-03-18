/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:29:22 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:31:38 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wcsnew(int n)
{
	wchar_t *wstr;

	wstr = (wchar_t *)malloc(sizeof(wchar_t *) * (++n));
	if (!wstr)
		return (NULL);
	while (n-- > 0)
		wstr[n] = '\0';
	return (wstr);
}
