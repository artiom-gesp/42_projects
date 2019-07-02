/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:35:24 by amanuel           #+#    #+#             */
/*   Updated: 2019/05/03 12:35:23 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft.h>
# include <stdarg.h>

typedef struct		s_id
{
	char			*p;
	short			plen;
	short			ins;
	va_list			vlst;
	char			hash;
	char			zero;
	char			minu;
	char			plus;
	char			spac;
	short			prec;
	short			widt;
	char			arg;
}					t_id;

int					ft_printf(char *s, ...);
void				ft_arg_di(t_id *id);
void				ft_arg_uox(t_id *id, char c);
void				ft_arg_s(t_id *id);
void				ft_arg_c(t_id *id);
void				ft_exe_flags(t_id *id, char **buff);

#endif
