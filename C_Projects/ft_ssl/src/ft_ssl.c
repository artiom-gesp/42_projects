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
    if (!isatty(fileno(stdin)))
        handle_noninteractive(&input);
    else
        handle_interactive(&input);
    handle_files(&input);
    print_console(input.console);
    print_string(input.strings);
    print_files(input.filenames);

    ssl_exit("", &input, 0);
}