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
            exit(-1);
        }
    }
    return flags;
}

void parser(int argc, char **argv, t_input *input)
{
    int8_t flags;

    flags = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' \
            && !(flags & FORBID_FLAGS) \
            && ft_strlen(argv[i]) > 1)
            {
                flags = get_flags(&argv[i][1], flags);
            }
        else
            flags |= FORBID_FLAGS;
            if (!input->filenames)
            {
                input->filenames = &(t_filename){0, NULL};
            }

    }

    return flags;
}