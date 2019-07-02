/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:57:17 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 20:25:11 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_arg_di(t_id *id)
{
	char		*buff;

	if (id->arg == 0)
		buff = ft_itoa(va_arg(id->vlst, int));
	else if (id->arg == 1)
		buff = ft_itoa((short)va_arg(id->vlst, int));
	else if (id->arg == 2)
		buff = ft_itoa((char)va_arg(id->vlst, int));
	else if (id->arg == 3)
		buff = ft_ltoa(va_arg(id->vlst, size_t));
	else
		buff = ft_ltoa(va_arg(id->vlst, long));
	if (id->prec == 0 && *buff == '0')
		*buff = 0;
	if ((*buff == '-' || id->plus) && (id->ins = 1) && *buff != '-')
		buff = ft_strjoin_free("+", buff, 2);
	else if (id->spac && (id->ins = 1) && *buff != '-')
		buff = ft_strjoin_free(" ", buff, 2);
	ft_exe_flags(id, &buff);
}

void			ft_arg_uox(t_id *id, char c)
{
	char		*buff;

	if (id->arg == 0)
		buff = ft_uitoa_base(va_arg(id->vlst, unsigned int), c);
	else if (id->arg == 1)
		buff = ft_uitoa_base((unsigned short)va_arg(id->vlst, int), c);
	else if (id->arg == 2)
		buff = ft_uitoa_base((unsigned char)va_arg(id->vlst, int), c);
	else
		buff = ft_ultoa_base(va_arg(id->vlst, unsigned long), c);
	if (*buff == '0' && (c == 8 || !(id->hash = 0)) && id->prec == 0)
		*buff = 0;
	if (id->hash && c == 8 && *buff != '0' && (id->ins = 1))
		buff = ft_strjoin_free("0", buff, 2);
	else if ((id->ins || id->hash) && c == 16 && (id->ins = 2))
		buff = ft_strjoin_free("0x", buff, 2);
	else if (id->hash && c == -16 && (id->ins = 2))
		buff = ft_strjoin_free("0X", buff, 2);
	ft_exe_flags(id, &buff);
}

void			ft_arg_s(t_id *id)
{
	char		*buff;

	if (id->arg != 4)
	{
		buff = ft_strdup(va_arg(id->vlst, char *));
		if (!buff && (id->prec = -1))
			buff = ft_strdup("(null)");
	}
	else
		buff = ft_itostr(va_arg(id->vlst, wchar_t *), 0);
	if (id->prec >= 0)
		buff = ft_strnjoin_free(buff, NULL, id->prec, 1);
	id->prec = -1;
	ft_exe_flags(id, &buff);
}

void			ft_arg_c(t_id *id)
{
	char		*buff;
	int			c;
	int			i;

	id->prec = -1;
	if ((c = va_arg(id->vlst, int)))
	{
		if (id->arg != 4)
			buff = ft_lilstr(c, 0, 0);
		else
			buff = ft_itostr(NULL, c);
		ft_exe_flags(id, &buff);
		return ;
	}
	if ((c = id->widt - 1) > 0 && !id->minu)
		id->p = ft_strjoin_free(id->p,
			ft_strset(ft_strnew(c), ' ', c), 3);
	if ((i = ft_strlen(id->p)) < 1)
		id->p = ft_strnew(0);
	write(1, id->p, i + 1);
	free(id->p);
	id->p = NULL;
	id->plen += i + 1;
	if (c > 0 && id->minu)
		id->p = ft_strset(ft_strnew(c), ' ', c);
}

void			ft_exe_flags(t_id *id, char **buff)
{
	int			i;

	if ((i = id->prec + id->ins - ft_strlen(*buff)) > 0 && **buff != '%')
		*buff = ft_strins_free(*buff,
				ft_strset(ft_strnew(i), '0', i), id->ins, 1);
	if ((i = id->widt - ft_strlen(*buff)) > 0)
	{
		if (id->minu)
			*buff = ft_strjoin_free(*buff,
					ft_strset(ft_strnew(i), ' ', i), 3);
		else if (id->zero && id->prec < 0)
			*buff = ft_strins_free(*buff,
					ft_strset(ft_strnew(i), '0', i), id->ins, 1);
		else
			*buff = ft_strjoin_free(ft_strset(ft_strnew(i),
				' ', i), *buff, 3);
	}
	id->p = ft_strjoin_free(id->p, *buff, 3);
}
