/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:24:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 17:27:29 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLIT_H
# define FT_FILLIT_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# define BUFF_SIZE 32

int	get_next_line(int fd, char **line);

#endif
