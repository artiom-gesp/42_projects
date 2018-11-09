# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 09:52:08 by agesp             #+#    #+#              #
#    Updated: 2018/11/09 15:36:35 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c \
	ft_memcpy.c \
	ft_strchr.c \
	ft_strlcat.c \
	ft_strncpy.c \
	ft_tolower.c \
	ft_atoi.c \
	ft_isascii.c \
	ft_memmove.c \
	ft_strcmp.c \
	ft_strlen.c \
	ft_strnstr.c \
	ft_toupper.c \
	ft_bzero.c \
	ft_isdigit.c \
	ft_memset.c \
	ft_strcpy.c \
	ft_strncat.c \
	ft_strrchr.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_strcat.c \
	ft_strdup.c \
	ft_strncmp.c \
	ft_strstr.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \

OBJ = ft_isalpha.o \
	ft_memcpy.o \
	ft_strchr.o \
	ft_strlcat.o\
	ft_strncpy.o \
	ft_tolower.o \
	ft_atoi.o \
	ft_isascii.o \
	ft_memmove.o\
	ft_strcmp.o \
	ft_strlen.o \
	ft_strnstr.o \
	ft_toupper.o \
	ft_bzero.o \
	ft_isdigit.o \
	ft_memset.o \
	ft_strcpy.o \
	ft_strncat.o \
	ft_strrchr.o \
	ft_isalnum.o \
	ft_isprint.o \
	ft_strcat.o \
	ft_strdup.o \
	ft_strncmp.o \
	ft_strstr.o \
	ft_memccpy.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_memalloc.o \
	ft_memdel.o \
	ft_strnew.o \
	ft_strdel.o \
	ft_strclr.o \
	ft_striter.o \
	ft_striteri.o \
	ft_strmap.o \
	ft_strmapi.o \
	ft_strequ.o \
	ft_strnequ.o \
	ft_strsub.o \
	ft_strjoin.o \
	ft_strtrim.o \

HEAD =  libft.h
all: $(NAME)

$(NAME):
	gcc -c $(SRC) $(HEAD) -Wall -Werror -Wextra
	ar -rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


