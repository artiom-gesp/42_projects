/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:50:37 by agesp             #+#    #+#             */
/*   Updated: 2019/01/22 15:26:41 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100

# include <fcntl.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>

int					get_next_line(int fd, char **line);

#endif
