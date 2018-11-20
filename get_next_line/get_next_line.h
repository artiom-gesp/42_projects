/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:50:37 by agesp             #+#    #+#             */
/*   Updated: 2018/11/20 17:15:56 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100

# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>

typedef struct	w_list
{
	char		*save_my_buff;
	int	fd;
	int			flag;
	struct w_list *next;
	struct w_list *prev;
}				my_list;

int				get_next_line(int fd, char **line);
char			*ft_strdup(const char *s1);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);

#endif
