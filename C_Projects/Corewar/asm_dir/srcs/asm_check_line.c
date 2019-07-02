/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:51:36 by amanuel           #+#    #+#             */
/*   Updated: 2019/06/11 13:07:46 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

/*
** Si un label est nommé dans la ligne, on l'enregistre avec sa position,
** dans la liste des labels
*/

static void		ft_named_label(t_asm *s)
{
	char		*label;
	int			*position;

	s->i = 0;
	while (ft_strchr(LABEL_CHARS, s->line[s->x + s->i]))
		s->i++;
	if (s->line[s->x + s->i] == LABEL_CHAR)
	{
		label = ft_strndup(s->line + s->x, s->i);
		s->named_lab = (char**)ft_addarray((void**)s->named_lab, (void*)label);
		position = (int*)ft_memalloc(sizeof(int));
		*position = s->champ_size;
		s->npos_lab = (int**)ft_addarray((void**)s->npos_lab, (void*)position);
		s->x += s->i + 1;
		s->x += ft_count_whitespace(s->line + s->x);
		if (s->line[s->x])
			ft_check_line(s);
	}
	else if (s->line[s->x])
		ft_exit(s, s->y, s->x, "Unknow action");
}

/*
** On mesure le nombre de lettres minuscules successives,
** et on les compare à la liste des actions possibles
** Si c'est une des 16 actions, son numéro est mis sur le 1er octet du maillon,
** et la ligne est envoyée dans transcript_actions
** Sinon on vérifie que ce n'est pas un commentaire
** Sinon on regarde si c'est un label
*/

void			ft_check_line(t_asm *s)
{
	s->i = 0;
	while (!s->i)
	{
		while (s->line[s->x + s->i] >= 97 && s->line[s->x + s->i] <= 122)
			s->i++;
		if (ft_strnstr(s->inst_lst, s->line + s->x, s->i)
		&& (s->line[s->x + s->i] == ' ' || s->line[s->x + s->i] == '\t'))
		{
			*s->fresh = (ft_strnstr(s->inst_lst,
						s->line + s->x, s->i) - s->inst_lst) / 6;
			s->x += s->i;
			s->x += ft_count_whitespace(s->line + s->x);
			s->size = 1;
			s->size += HAS_SUM[(int)*s->fresh];
			ft_transcript_actions(s);
		}
		else if (s->line[s->x] == COMMENT_CHAR)
			return ;
		else
			ft_named_label(s);
	}
}

/*
** Tant que les noms et commentaires n'ont pas été achevés,
** les lignes sont entrées dans le 1er maillon.
*/

static void		ft_name_comment(t_asm *s, char *cmd, int len_max, char *type)
{
	if (!(s->name_com % 2) && ++s->name_com)
		if ((s->j = ft_strlen(cmd))
		&& (!(!ft_strncmp(s->line + s->x, cmd, s->j)
		&& (s->x += s->j + ft_count_whitespace(s->line + s->x + s->j) + 1)
		&& (s->line[s->x - 1] == '"'))))
			ft_exit(s, s->y, 1, "Bad name/comment");
	if (ft_strchr(s->line + s->x, '"') && ++s->name_com)
	{
		s->j = ft_strchr(s->line + s->x, '"') - (s->line + s->x);
		if ((s->i += s->j) <= len_max
		|| (ft_printf("Champion %s too long (Max length %d)\n", type, len_max)
		&& ft_exit(s, 0, 0, NULL)))
			ft_strncpy(s->fresh, s->line + s->x, s->j);
		s->fresh = (char*)s->part->content + 4 + len_max + 8;
		s->x += s->j + 1;
		ft_check_endline(s);
	}
	else
	{
		s->j = ft_strlen(s->line) - s->x;
		ft_strncpy(s->fresh, s->line + s->x, s->j);
		s->fresh += s->j;
		*(s->fresh++) = '\n';
		s->i += s->j + 1;
	}
}

/*
** On vérifie la fin de la ligne une fois qu'elle a été traitée
*/

void			ft_check_endline(t_asm *s)
{
	if (s->line[s->x])
		s->x += ft_count_whitespace(s->line + s->x);
	if (s->line[s->x] && s->line[s->x] != COMMENT_CHAR && s->line[s->x] != '\n')
		ft_exit(s, s->y, s->x, "Bad end of line");
}

/*
** Tout d'abord la liste chaînée est initialisée à la taille définie dans le .h
** Puis la ligne par dans la gestion name/comment
** Puis les instructions sont enregistrées dans une liste chainée
** Un maillon de liste est initialisé et la ligne est envoyée dans check_line
** Enfin la taille du maillon est définie et celle du champion actualisée
*/

void			ft_transcript(t_asm *s)
{
	if (!s->initialization && ++s->initialization)
	{
		s->part = ft_lstaddnew(NULL, NULL,
					4 + PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + 4);
		s->first_part = s->part;
		s->fresh = (char*)s->part->content + 4;
	}
	if (!(s->name_com % 2))
		s->x += ft_count_whitespace(s->line);
	if (s->name_com <= 1 && s->line[s->x] && s->line[s->x] != COMMENT_CHAR)
		ft_name_comment(s, NAME_CMD_STRING, PROG_NAME_LENGTH, "name");
	else if (s->name_com <= 3 && s->line[s->x] && s->line[s->x] != COMMENT_CHAR)
		ft_name_comment(s, COMMENT_CMD_STRING, COMMENT_LENGTH, "comment");
	else if (s->line[s->x] && s->line[s->x] != COMMENT_CHAR)
	{
		s->part = ft_lstaddnew(s->part, NULL, 11);
		s->fresh = s->part->content;
		s->sum = 0;
		s->size = 0;
		ft_check_line(s);
		ft_check_endline(s);
		s->part->content_size = s->size;
		s->champ_size += s->size;
	}
	ft_memdel((void**)&s->line);
}
