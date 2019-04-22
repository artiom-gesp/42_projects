/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:36:59 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:50:34 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

char			*ft_strchr(const char *str, int c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar(char c);
void			ft_putnbr(intmax_t n);
void			ft_putstr(const char *s);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strjoin(char *s1, char *s2);
intmax_t		ft_strlen(const char *s);
char			*ft_strsub(const char*s, unsigned int start, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strnstr(const char *str, const char *to_find, size_t n);
int				ft_atoi(const char **nbr);
unsigned int	ft_abs(int n);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpyend(char *s1, char *s2);
char			*ft_strdup(const char *s1);
char			*ft_strnew(size_t size);
char			*ft_strncat(char *s1, const char *s2, size_t n);
void			freestr(char *str);
void			freewstr(wchar_t *wstr);
wchar_t			*ft_wcsnew(int n);
int				ft_wcslen(wchar_t *wstr);
wchar_t			*ft_wcscpy(wchar_t *dest, wchar_t *src);
wchar_t			*ft_wcsdup(wchar_t *src);
wchar_t			*ft_wcscat(wchar_t *dest, const wchar_t *src);
int				ft_wstrlen(wchar_t *wstr);
int				ft_wcharlen(wchar_t c);
void			ft_putwstr(wchar_t *wstr);
void			ft_putwchar(wchar_t chr);

#endif
