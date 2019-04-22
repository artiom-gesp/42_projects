NAME=libft.a

SRCS=ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_strlen.c\
	ft_strdup.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strnstr.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_atoi.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_memcmp.c\
	ft_memalloc.c\
	ft_memdel.c\
	ft_strnew.c\
	ft_strdel.c\
	ft_strclr.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_strsplit.c\
	ft_itoa.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putnbr_fd.c\
	ft_putendl_fd.c\
	ft_putendl.c\
	ft_putnbr.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_strcpyend.c\
	freestr.c\
	freewstr.c\
	ft_wcsnew.c\
	ft_wcslen.c\
	ft_wcscpy.c\
	ft_wcsdup.c\
	ft_wcscat.c\
	ft_wstrlen.c\
	ft_wcharlen.c\
	ft_putwstr.c\
	ft_putwchar.c\
	get_next_line.c\
	free_2mem.c\
	ft_abs.c\
	ft_ishexa.c\
	ft_atoi_base.c\
	ft_hexa.c\
	tool.c\
	tool_is.c\
	parsing_glob.c\
	printf.c\
	init_attr.c\
	init_conv.c\
	init_glob.c\
	init_mod_long.c\
	init_prec.c\
	controller_attr.c\
	controller_mod_long.c\
	controller_wstr.c\
	tool_controller.c\
	conv_dec.c\
	conv_string.c\
	itoa_base.c\
	ft_atoi_adv.c\
	ft_intcpy.c\
	ft_strichr.c\
	ft_atoii.c\
	
OBJS= $(SRCS:.c=.o)

FLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(SRC)
	@gcc -c $(FLAGS) $(SRCS) 
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re
