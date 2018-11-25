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

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# define BUFF_SIZE 32

int		get_next_line(int fd, char **line);
char	**make_tab(char *file);
void	is_bc(int tab[], char **tetr, int i);
void	is_z(int tab[], char **tetr, int i);
void	is_mp(int tab[], char **tetr, int i);
void	is_l(int tab[], char **tetr, int i);
void	is_rev_l(int tab[], char **tetr, int i);

#endif
