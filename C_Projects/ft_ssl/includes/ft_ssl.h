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

# define BUFFER_SIZE 5

# define MD5 0
# define SHA256 1

typedef struct s_filename
{
    char *name;
    struct s_filename *next;
}               t_filename;

typedef struct s_digest
{
    char *digest;
    struct s_digest *next;
}              t_digest; 

typedef struct s_input
{
    int8_t alg;
    char *(*alg_func)(char*);
    int8_t flags;
    t_filename *filenames;
    t_digest *digests;
}               t_input;

/*
Parsing
*/
void parser(int argc, char **argv, t_input *input);

void ssl_exit(char *msg, t_input *input, int8_t code);

void handle_files(t_input *input);

/*
Crypto
*/
char *ft_md5(char *str);
char *ft_sha256(char *str);

#endif