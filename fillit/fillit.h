/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:05:08 by agesp             #+#    #+#             */
/*   Updated: 2018/12/13 09:48:09 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define BUFF_SIZE 1
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft/libft.h"

char				**make_tab(char *file);
int					get_next_line(const int fd, char **line);
void				create_int_tab(int tab[][32], int size);
void				print_result(int to_fill[][32], int size);
int					check_entry(char **tab);
int					ft_solve(int tetr[], int tab[][32], int i, int j);
void				free_tab(char **tab);

void				is_bc(int tab[], char **tetr, int i, int pos);
void				is_z(int tab[], char **tetr, int i, int pos);
void				is_mp(int tab[], char **tetr, int i, int pos);
void				is_l(int tab[], char **tetr, int i, int pos);
void				is_rev_l(int tab[], char **tetr, int i, int pos);
void				extr_tetr(char **tetr, int tab[]);
int					call_canplace(int tetr, int to_fill[][32], int i, int j);

int					canplace1(int tab[][32], int i, int j, int c);
int					canplace2(int tab[][32], int i, int j, int c);
int					canplace3(int tab[][32], int i, int j, int c);
int					canplace4(int tab[][32], int i, int j, int c);
int					canplace5(int tab[][32], int i, int j, int c);
int					canplace6(int tab[][32], int i, int j, int c);
int					canplace7(int tab[][32], int i, int j, int c);
int					canplace8(int tab[][32], int i, int j, int c);
int					canplace9(int tab[][32], int i, int j, int c);
int					canplace10(int tab[][32], int i, int j, int c);
int					canplace11(int tab[][32], int i, int j, int c);
int					canplace12(int tab[][32], int i, int j, int c);
int					canplace13(int tab[][32], int i, int j, int c);
int					canplace14(int tab[][32], int i, int j, int c);
int					canplace15(int tab[][32], int i, int j, int c);
int					canplace16(int tab[][32], int i, int j, int c);
int					canplace17(int tab[][32], int i, int j, int c);
int					canplace18(int tab[][32], int i, int j, int c);
int					canplace19(int tab[][32], int i, int j, int c);

#endif
