/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:51:35 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

char		*straddnchar(char *str, int check, int n, char c)
{
	int		i;
	int		length;
	char	*new;

	length = ft_strlen(str);
	new = ft_strnew(length + n);
	i = 0;
	if (check)
	{
		new = ft_strcpy(new, str);
		while (i < n)
			new[length + i++] = c;
	}
	else
	{
		while (i < n)
			new[i++] = c;
		new = ft_strcat(new, str);
	}
	freestr(str);
	return (new);
}

char		*straddncharsigned(char *str, int n, char c)
{
	int		i;
	int		length;
	char	*new;
	int		sign;

	length = ft_strlen(str);
	new = ft_strnew(length + n);
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
		sign = 1;
	else
		sign = 0;
	if (sign)
		new = ft_strncat(new, str, 1);
	i = sign;
	while (i < n + sign)
	{
		new[i] = c;
		i++;
	}
	new = ft_strcat(new, &str[sign]);
	freestr(str);
	return (new);
}

char		*addhexachar(char *str, int ishexa, char *s1)
{
	int		length;
	char	*new;

	length = ft_strlen(str);
	if (!(length == 1 && str[0] == '0' && ishexa))
	{
		new = ft_strnew(length + 2);
		new = ft_strcat(new, s1);
		new = ft_strcat(new, str);
		freestr(str);
	}
	else
		new = str;
	return (new);
}

char		*addoctachar(char *str)
{
	int		length;
	char	*new;

	length = ft_strlen(str);
	if (!(length == 1 && str[0] == '0'))
	{
		new = ft_strnew(length + 1);
		new = ft_strcat(new, "0");
		new = ft_strcat(new, str);
		freestr(str);
	}
	else
		new = str;
	return (new);
}
