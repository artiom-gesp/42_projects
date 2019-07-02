/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:41:00 by amanuel           #+#    #+#             */
/*   Updated: 2019/06/01 16:31:08 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/libft.h"

# define BONUS_TYPE_ERROR		1
# define BONUS_FILE_DIR			1

# define HAS_SUM				(int[17]){0,0,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1}
# define HALFSIZE				(char[17]){0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0}

typedef struct					s_asm
{
	int							file_name_size;
	int							fd;
	char						*line;
	int							y;
	int							x;
	uint8_t						sum;
	uint8_t						**checksum;
	char						*inst_lst;
	struct s_list				*first_part;
	struct s_list				*part;
	char						initialization;
	char						name_com;

	int							size;
	int							champ_size;
	char						**named_lab;
	int							**npos_lab;
	char						**called_lab;
	int							**cpos_lab;
	void						**p_lst;

	char						*fresh;
	int							i;
	int							j;
}								t_asm;

void							ft_transcript(t_asm *s);
void							ft_transcript_actions(t_asm *s);
void							ft_check_line(t_asm *s);
void							ft_check_endline(t_asm *s);
char							ft_exit(t_asm *s, int y, int x, char *str);
void							ft_file_location(t_asm *s, char *av);

#endif
