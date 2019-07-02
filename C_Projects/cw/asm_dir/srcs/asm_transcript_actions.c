/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_transcript_actions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:51:36 by amanuel           #+#    #+#             */
/*   Updated: 2019/06/11 13:45:01 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

/*
** Lorsqu'un label est appelé, on enregistre le nom appelé, sa position,
** et un pointeur sur les 2/4 octets (tel que défini dans le .h),
** dans la liste des labels appelés
*/

static void		ft_called_label(t_asm *s, char bits)
{
	char		*label;
	int			*position;

	s->j = 0;
	while (s->line[s->x + s->j] && ft_strchr(LABEL_CHARS, s->line[s->x + s->j]))
		s->j++;
	if (s->j)
	{
		label = ft_strndup(s->line + s->x, s->j);
		s->called_lab = (char**)ft_addarray(
					(void**)s->called_lab, (void*)label);
		position = (int*)ft_memalloc(sizeof(int) * 4);
		position[0] = s->champ_size;
		position[1] = bits;
		position[2] = s->y;
		position[3] = s->x;
		s->cpos_lab = (int**)ft_addarray((void**)s->cpos_lab, (void*)position);
		s->p_lst = ft_addarray(s->p_lst, s->fresh + s->size);
		s->x += s->j;
		s->x += ft_count_whitespace(s->line + s->x);
	}
	else
		ft_exit(s, s->y, s->x, "Bad indirect");
}

/*
** On vérifie s'il y a le label char du .h,
** ou que le direct est un nombre
** Si c'est un label, on enregistre le nom appelé, sa position,
** et un pointeur sur les deux ou quatre octets (tel que défini dans le .h),
** dans la liste des labels appelés
** Si c'est un nombre on le met sur les 2/4 octets (tel que défini dans le .h)
** Puis on actualise la size et la checksum
*/

static void		ft_action_direct(t_asm *s)
{
	if (s->line[s->x] == LABEL_CHAR && HALFSIZE[(int)*s->fresh] && ++s->x)
		ft_called_label(s, 16);
	else if (s->line[s->x] == LABEL_CHAR && ++s->x)
		ft_called_label(s, 32);
	else if (ft_isint(s->line + s->x, 32))
	{
		s->j = ft_atoi(s->line + s->x);
		if (HALFSIZE[(int)*s->fresh])
			*(short*)(s->fresh + s->size) = ft_reverse_int(s->j, 16);
		else
			*(int*)(s->fresh + s->size) = ft_reverse_int(s->j, 32);
		s->x += ft_isint(s->line + s->x, 32);
	}
	else
		ft_exit(s, s->y, s->x, "Bad direct");
	s->i++;
	s->sum += ft_pow(2, 8 - ((2 * s->i) - 1));
	s->size += 2;
	if (!HALFSIZE[(int)*s->fresh])
		s->size += 2;
	s->x += ft_count_whitespace(s->line + s->x);
}

/*
** On vérifie qu'il y a le label char du .h,
** ou que l'indirect est un nombre
** Si c'est un label, on enregistre le nom appelé, sa position,
** et un pointeur sur les deux octets, dans la liste des labels appelés
** Si c'est un nombre on le met sur les deux octets
** Puis on actualise la size et la checksum
*/

static void		ft_action_indirect(t_asm *s)
{
	if (s->line[s->x] == LABEL_CHAR && ++s->x)
		ft_called_label(s, 16);
	else
	{
		s->j = ft_atoi(s->line + s->x);
		*(short*)(s->fresh + s->size) = ft_reverse_int(s->j, 16);
		s->x += ft_isint(s->line + s->x, 16);
	}
	s->i++;
	s->sum += ft_pow(2, 8 - ((2 * s->i) - 1)) + ft_pow(2, 8 - (2 * s->i));
	s->size += 2;
	s->x += ft_count_whitespace(s->line + s->x);
}

/*
** On vérifie que le registre est un nombre, strictement positif,
** et strictement inférieur à la limite du .h et 255 (car max de 1 octet)
** Puis on met le registre sur le maillon et on actualise la size et la checksum
*/

static void		ft_action_register(t_asm *s)
{
	if (ft_isint(s->line + s->x, 32)
	&& (s->j = ft_atoi(s->line + s->x))
	&& s->j >= 1 && s->j <= REG_NUMBER && s->j <= 255)
		s->fresh[s->size] = s->j;
	else
		ft_exit(s, s->y, s->x, "Bad register");
	s->x += ft_isint(s->line + s->x, 32);
	s->i++;
	s->sum += ft_pow(2, 8 - (2 * s->i));
	s->size += 1;
	s->x += ft_count_whitespace(s->line + s->x);
}

/*
** Tant que les 1, 2, ou 3 actions n'ont pas été traité, la fonction boucle
** Chaque type d'action est envoyée dans la fonction lui correspondant
** Une fois le bon nombre d'actions traité, la checksum est vérifiée,
** et si le .h détermine qu'elle doit figurer dans le .cor,
** elle est mise sur le deuxième octet du maillon
*/

void			ft_transcript_actions(t_asm *s)
{
	s->i = 0;
	while (s->i < *s->checksum[(int)*s->fresh])
	{
		if (s->i && (s->line[s->x] == SEPARATOR_CHAR))
			s->x += 1 + ft_count_whitespace(s->line + s->x + 1);
		else if (s->i)
			ft_exit(s, s->y, s->x, "Missing separator");
		if (s->line[s->x] == 'r' && ++s->x)
			ft_action_register(s);
		else if (s->line[s->x] == LABEL_CHAR || ft_isint(s->line + s->x, 32))
			ft_action_indirect(s);
		else if (s->line[s->x] == DIRECT_CHAR && ++s->x)
			ft_action_direct(s);
		else
			ft_exit(s, s->y, s->x, "Invalid action");
	}
	if (!ft_strchr((char*)s->checksum[(int)*s->fresh], s->sum))
		ft_exit(s, s->y, s->x, "Instructions unauthorized");
	else if (HAS_SUM[(int)*s->fresh])
		s->fresh[1] = s->sum;
}
