/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:36:55 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:37:26 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVER_H
# define CONVER_H

t_conv g_convtab[] =
{
	{'d', &conv_decimal},
	{'D', &conv_decimal},
	{'i', &conv_decimal},
	{'o', &conv_udecimal},
	{'O', &conv_udecimal},
	{'u', &conv_udecimal},
	{'U', &conv_udecimal},
	{'x', &conv_udecimal},
	{'X', &conv_udecimal},
	{'c', &conv_string},
	{'C', &conv_wstr},
	{'s', &conv_string},
	{'S', &conv_wstr},
	{'p', &conv_void_p},
	{'n', &conv_int_p},
	{'%', &conv_string},
	{'b', &conv_udecimal},
	{'r', &conv_string},
};

#endif
