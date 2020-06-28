/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <agesp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 13:41:30 by agesp             #+#    #+#             */
/*   Updated: 2020/06/19 15:54:30 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void save_s_flag(char *str, t_input *input)
{
    
}

int8_t get_flags(char *flag_list, int8_t flags)
{
    int i = -1;
    
    while (flag_list[++i])
    {   
        if (flag_list[i] == 'p')
            flags |= CONSOLE_FLAG;
        else if (flag_list[i] == 'r')
            flags |= REVERSE_FLAG;
        else if (flag_list[i] == 'q')
            flags |= QUIET_FLAG;
        else if (flag_list[i] == 's')
            flags |= STRING_FLAG;
        else
        {
            ft_printf("Unrecognized flag : -%c\n", flag_list[i]);
            return 0;
        }
    }
    return flags;
}

t_filename *allocate_filename(char *name)
{
    t_filename *filename;

    if (!(filename = malloc(sizeof(t_filename))))
        return NULL;
    else
    {
        filename->name = name;
        filename->next = NULL;
        return filename;
    }
}

void parse_digest(char *digest, t_input *input)
{
    if (!ft_strcmp(digest, "md5"))
        input->alg_func = &ft_md5;
    else if (!ft_strcmp(digest, "sha256"))
        input->alg_func = &ft_sha256;
    else
    {
        ft_printf("Invalid command '%s'; type \"help\" for a list.", digest);
        ssl_exit("", input, -1);
    }
}

void parse_flags(char *flags, t_input *input)
{
    if (ft_strlen(flags) <= 1)
        ssl_exit("Missing flag after -\n", input, -1);
    if (!(input->flags & FORBID_FLAGS))
        input->flags = get_flags(&flags[1], input->flags);
    if (input->flags == 0)
        ssl_exit("", input, -1);
}

void parse_filenames(char *filename, t_input *input)
{
    t_filename *filenames;

    filenames = NULL;
    input->flags |= FORBID_FLAGS;
    if (!input->filenames)
    {
        if (!(input->filenames = allocate_filename(filename)))
            ssl_exit("Malloc failed\n", input, -1);
    }
    else
    {
        filenames = input->filenames;
        while (filenames->next)
            filenames = filenames->next;
        if (!(filenames->next = allocate_filename(filename)))
            ssl_exit("Malloc failed\n", input, -1);
        filenames = filenames->next;
    }
}

void parser(int argc, char **argv, t_input *input)
{
    input->flags = 0;
    parse_digest(argv[1], input);
    if (argc <= 2)
        input->flags |= CONSOLE_FLAG; 
    for (int i = 2; i < argc; i++)
    {
        if (ft_strlen(argv[i]) > 0 && argv[i][0] == '-')
        {
            parse_flags(argv[i], input);
            if (input->flags & STRING_FLAG)
            {
                continue;
            }
        }
        else
            parse_filenames(argv[i], input);
    }
}