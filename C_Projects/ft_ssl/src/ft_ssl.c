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
    char buffer[5];
    char *line;

    input = (t_input){0, NULL};
    parser(argc, argv, &input);
    printf("%s\n", ft_itoa_base(input.flags, 2, 'a'));
    line = "";
    while (input.filenames)
    {
        printf("%s\n", input.filenames->name);
        input.filenames = input.filenames->next;
    }
    while ((input.flags & CONSOLE_FLAG) && fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        ft_printf("line : %s", line);
        line = realloc()
    }
    printf("%d\n", sizeof(buffer));
    return 0;
}