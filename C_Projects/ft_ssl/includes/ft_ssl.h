/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <agesp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 13:20:43 by agesp             #+#    #+#             */
/*   Updated: 2020/06/19 15:49:24 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include "libft.h"
# include "ft_printf.h"
# include <stdint.h>

# define FORBID_FLAGS 1
# define CONSOLE_FLAG 2
# define REVERSE_FLAG 4
# define QUIET_FLAG 8
# define STRING_FLAG 16

typedef struct s_filename
{
    char *name;
    struct s_filename *next;
}               t_filename;

typedef struct s_input
{
    int8_t flags;
    t_filename *filenames;
    
}               t_input;

void parser(int argc, char **argv, t_input *input);

#endif