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

void parser(int argc, char **argv, t_input *input)
{
    t_filename *filenames;

    filenames = NULL;
    input->flags = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (ft_strlen(argv[i]) <= 1)
                ssl_exit("Missing flag after -\n", input);
            if (!(input->flags & FORBID_FLAGS))
                input->flags = get_flags(&argv[i][1], input->flags);
            if (input->flags == 0)
                ssl_exit("", input);
        }
        else
        {
            input->flags |= FORBID_FLAGS;
            if (!filenames)
            {
        	    if (!(filenames = allocate_filename(argv[i])))
                    ssl_exit("Malloc failed\n", input);
                input->filenames = filenames;
            }
            else
            {
        	    if (!(filenames->next = allocate_filename(argv[i])))
                    ssl_exit("Malloc failed\n", input);
                filenames = filenames->next;
            }
        }
    }
}