/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <agesp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:41:34 by agesp             #+#    #+#             */
/*   Updated: 2020/06/19 15:51:04 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int main(int argc, char **argv)
{
    t_input input;
    char buffer[BUFFER_SIZE];
    char *line;

    if (argc <= 1)
    {
        ft_printf("usage: ft_ssl command [command opts] [command args]\n");
        return -1;
    }

    input = (t_input){0, NULL, 0, NULL, NULL, NULL};
    parser(argc, argv, &input);
    line = NULL;
    while ((input.flags & CONSOLE_FLAG) && fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (line && !ft_strstr(line, "\n"))
        {
            line = realloc(line, ft_strlen(line) + ft_strlen(buffer) + 1);
            line = ft_strcat(line, buffer);
        }
        else
        {
            line = calloc(BUFFER_SIZE, sizeof(char));
            line = ft_strcpy(line, buffer);
        }
        if ((ft_strlen(buffer) + 1 < BUFFER_SIZE) || ft_strstr(buffer, "\n"))
        {
            ft_printf("line : %s", buffer);
            add_to_console(input.alg_func(line), &input, line);
            input.alg_func(line);
            line = NULL;
        }
    }
    if (line)
    {
        add_to_console(input.alg_func(line), &input, line);
        input.alg_func(line);
    }
    handle_files(&input);
    print_console(input.console);
    print_files(input.filenames);

    ssl_exit("", &input, 0);
}