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
    t_filename filenames;

    input = (t_input){0, &filenames};
    parser(argc, argv, &input);
    while ((flags & CONSOLE_FLAG))
    {
        input = get_input()
    }
    return 0;
}