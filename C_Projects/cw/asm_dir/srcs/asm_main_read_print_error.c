/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main_read_print_error.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 02:26:05 by amanuel           #+#    #+#             */
/*   Updated: 2019/06/13 07:42:32 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

/*
** La liste des labels appelés est déroulées
** Pour chaque appel il y a un pointeur sur lequel on met la valeur
** Puis on free la mémoire de ces tableaux
*/

static void		ft_put_labels_value(t_asm *s, char ret)
{
	s->i = 0 + (-1);
	while (!ret && s->called_lab && s->called_lab[++s->i])
	{
		s->j = -1;
		if ((s->j = ft_strtab(s->named_lab, s->called_lab[s->i])) >= 0)
		{
			if (s->cpos_lab[s->i][1] == 16)
				*(short*)(s->p_lst[s->i]) = ft_reverse_int(*s->npos_lab[s->j]
							- *s->cpos_lab[s->i], 16);
			else
				*(int*)(s->p_lst[s->i]) = ft_reverse_int(*s->npos_lab[s->j]
							- *s->cpos_lab[s->i], 32);
		}
		else
			ft_exit(s, s->cpos_lab[s->i][2], s->cpos_lab[s->i][3],
						"Invalid label");
	}
	ft_freetab((void**)s->named_lab);
	ft_freetab((void**)s->npos_lab);
	ft_freetab((void**)s->called_lab);
	ft_freetab((void**)s->cpos_lab);
	free(s->p_lst);
}

/*
** Appelée par le main ou par la fonction exit, print, free puis renvoie 0 ou -1
** Nous commençons par la gestion des labels
** Si tout est ok (ret == 0), le fichier est créé, la liste imprimée et free
** Ensuite nous libérons la mémoire avant de finir
*/

static char		ft_print_and_free(t_asm *s, char *av, char ret, t_list *byebye)
{
	ft_put_labels_value(s, ret);
	s->part = s->first_part;
	if (!ret && BONUS_FILE_DIR)
		ft_file_location(s, av);
	else if (!ret)
	{
		s->fresh = ft_strndup(av, s->file_name_size - 2);
		s->fresh = ft_strjoin_free(s->fresh, ".cor", 1);
		ft_printf("Writing output program to %s\n", s->fresh);
		s->fd = open(s->fresh, O_RDWR | O_CREAT | O_TRUNC, 0644);
		free(s->fresh);
	}
	while (s->part)
	{
		if (!ret)
			ft_putvoid_fd(s->part->content, s->part->content_size, s->fd);
		free(s->part->content);
		byebye = s->part;
		s->part = s->part->next;
		free(byebye);
	}
	ft_freetab((void**)s->checksum);
	free(s->inst_lst);
	free(s);
	return (ret);
}

/*
** La fonction exit est appelée lorsque une erreur est détectée
** Elle fixe la valeur de retour à -1
** Avant d'exit elle passe par la fonction print & free, qui ne fera que free
*/

char			ft_exit(t_asm *s, int y, int x, char *str)
{
	s->y = y;
	s->x = x;
	if (str && BONUS_TYPE_ERROR)
		ft_printf("%s\n", str);
	if (s->y)
		ft_printf("Lexical error at [%d:%d]\n", s->y, s->x);
	if (s->line)
		ft_memdel((void**)&s->line);
	ft_print_and_free(s, NULL, -1, NULL);
	exit(-1);
}

/*
** On initialise les constantes que la norme nous defend de definir dans le .h
** Le tableau des checksum initialisé en long, il sera ensuite utilisé en char
** Ainsi qu'une string de la liste des actions possibles
*/

static void		ft_checksum_initialization(t_asm *s, uint64_t **wtf)
{
	s->checksum = (uint8_t**)ft_tabnew(17, 16, 8);
	wtf = (uint64_t**)s->checksum;
	wtf[1][0] = 32769;
	wtf[2][0] = 9490434;
	wtf[3][0] = 5271554;
	wtf[4][0] = 21507;
	wtf[5][0] = 21507;
	wtf[6][0] = 8400520301525660675;
	wtf[6][1] = 21604;
	wtf[7][0] = 8400520301525660675;
	wtf[7][1] = 21604;
	wtf[8][0] = 8400520301525660675;
	wtf[8][1] = 21604;
	wtf[9][0] = 32769;
	wtf[10][0] = 23754487627047939;
	wtf[11][0] = 23741086316132355;
	wtf[12][0] = 32769;
	wtf[13][0] = 9490434;
	wtf[14][0] = 23754487627047939;
	wtf[15][0] = 32769;
	wtf[16][0] = 16385;
	s->inst_lst = ft_strdup("______live__ld____st____add___sub___and___");
	s->inst_lst = ft_strjoin_free(s->inst_lst,
	"or____xor___zjmp__ldi___sti___fork__lld___lldi__lfork_aff___", 1);
}

/*
** Après avoir fait quelques vérifications,
** on envoie chaque ligne dans la fonction transcript
** Puis une fois terminé on finit avec la fonction print & free
*/

int				main(int ac, char **av)
{
	t_asm		*s;

	s = (t_asm*)ft_memalloc(sizeof(t_asm));
	ft_checksum_initialization(s, NULL);
	if (ac <= 1)
		ft_exit(s, s->y, s->x, "Nombre d'arguments insuffisant");
	else if ((s->fd = open(*(++av), O_RDONLY)) > 2
	&& (lseek(s->fd, 0, SEEK_END) > 0)
	&& (s->file_name_size = ft_strlen(*av)) > 2
	&& !(ft_strcmp(".s", *av + s->file_name_size - 2)))
	{
		close(s->fd);
		s->fd = open(*av, O_RDONLY);
		while (get_next_line(s->fd, &s->line) > 0
		&& ++s->y && !(s->x = 0))
			ft_transcript(s);
		*(int*)s->first_part->content = ft_reverse_int(COREWAR_EXEC_MAGIC, 32);
		*(int*)(s->first_part->content + 8 + PROG_NAME_LENGTH) = ft_reverse_int(
				s->champ_size, 32);
		close(s->fd);
	}
	else
		ft_exit(s, s->y, s->x, "Fichier invalide");
	return (ft_print_and_free(s, *av, 0, NULL));
}
