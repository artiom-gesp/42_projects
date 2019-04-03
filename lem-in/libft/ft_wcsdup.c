/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:29:22 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:31:38 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wcsdup(wchar_t *src)
{
	wchar_t	*wstr;

	wstr = (wchar_t *)malloc(sizeof(wchar_t *) * (ft_wcslen(src) + 1));
	if (!wstr)
		return (NULL);
	ft_wcscpy(wstr, src);
	return (wstr);
}
