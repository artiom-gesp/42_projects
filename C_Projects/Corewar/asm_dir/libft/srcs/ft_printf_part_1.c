/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:57:17 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 20:18:50 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		ft_type(char **s, t_id *id)
{
	char		*buff;

	if (**s == 'D' || **s == 'U' || **s == 'O' ||
			**s == 'C' || **s == 'S' || **s == 'p')
		id->arg = 4;
	if (**s == 'i' || **s == 'd' || **s == 'D')
		ft_arg_di(id);
	else if (**s == 'x' || (**s == 'p' && (id->ins = 1)))
		ft_arg_uox(id, 16);
	else if (**s == 's' || **s == 'S')
		ft_arg_s(id);
	else if (**s == 'c' || **s == 'C')
		ft_arg_c(id);
	else if (**s == 'X')
		ft_arg_uox(id, -16);
	else if (**s == 'u' || **s == 'U')
		ft_arg_uox(id, 10);
	else if (**s == 'o' || **s == 'O')
		ft_arg_uox(id, 8);
	else if (**s == '%' && (buff = ft_strdup("%")))
		ft_exe_flags(id, &buff);
	else
		return (0);
	++*s;
	return (1);
}

static void		ft_id_init(t_id *id)
{
	id->ins = 0;
	id->hash = 0;
	id->zero = 0;
	id->minu = 0;
	id->plus = 0;
	id->spac = 0;
	id->prec = -1;
	id->widt = 0;
	id->arg = 0;
}

static char		ft_flags2(char **s, t_id *id)
{
	if (**s == '.' && ++*s && !(id->prec = 0))
	{
		if (**s >= '1' && **s <= '9' && (id->prec = ft_atoi(*s)))
			while (**s >= '0' && **s <= '9')
				++*s;
	}
	else if (**s >= '1' && **s <= '9' && (id->widt = ft_atoi(*s)))
	{
		while (**s >= '0' && **s <= '9')
			++*s;
	}
	else if (**s == 'h' && ++*s && ((id->arg <= 1 && id->arg++) || 1))
		;
	else if (**s == 'z' && ++*s)
		id->arg = 3;
	else if ((**s == 'l' || **s == 'j') && ++*s)
		id->arg = 4;
	else
		return (0);
	return (1);
}

static void		ft_save_flags1(char **s, t_id *id)
{
	char		*buff;

	ft_id_init(id);
	while (!(ft_type(s, id)))
	{
		if (**s == '#' && ++*s)
			id->hash = 1;
		else if (**s == '0' && ++*s)
			id->zero = 1;
		else if (**s == '-' && ++*s)
			id->minu = 1;
		else if (**s == '+' && ++*s)
			id->plus = 1;
		else if (**s == ' ' && ++*s)
			id->spac = 1;
		else if (!ft_flags2(s, id))
		{
			if (**s && (buff = ft_lilstr(**s, 0, 0)) && ++*s)
				ft_exe_flags(id, &buff);
			return ;
		}
	}
}

int				ft_printf(char *s, ...)
{
	t_id		id;
	short		i;

	va_start(id.vlst, s);
	id.p = NULL;
	id.plen = 0;
	while (*s && !(i = 0))
	{
		while (s[i] && s[i] != '%')
			i++;
		if (i)
			id.p = ft_strjoin_free(id.p, ft_strndup(s, i), 3);
		if (*(s += i) && *(++s))
			ft_save_flags1(&s, &id);
	}
	if ((i = ft_strlen(id.p)))
	{
		write(1, id.p, i);
		free(id.p);
	}
	return (id.plen += i);
}
