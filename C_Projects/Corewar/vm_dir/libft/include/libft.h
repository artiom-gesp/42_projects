/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:41:52 by pfragnou          #+#    #+#             */
/*   Updated: 2019/04/12 14:41:53 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;

}					t_list;

int					ft_atoi(const char *str);
int					ft_count_whitespace(char *s);
t_list				*ft_lstaddnew_free(t_list *old, void *content,
	size_t content_size);
void				*ft_memalloc(size_t size);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strndup(char *s1, short i);
char				*ft_strjoin_f(char *s1, char *s2, uint8_t opt);
char				ft_strcpy(char *dst, const char *src);
int					ft_strtab(char **tab, char *to_find);
size_t				ft_strlen(char *s);
int					ft_swap_int16(int nb);
int					ft_swap_int32(int nb);
void				*ft_memset(void *b, int c, size_t n);
int					ft_findchar(char *str, char c);

#endif
