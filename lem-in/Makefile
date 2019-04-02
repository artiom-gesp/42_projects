CC			=	gcc
NAME		=	lem-in
VISU		=	visu
FLAGS		=	-Wall -Wextra -Werror
LIBDIR		=	libft
LIBLINK		=	-L $(LIBDIR) -lft
LIB 		=	$(LIBDIR)/libft.a
LIB_VISU	=	-framework Opengl -framework AppKit

INCLUDES	= 	-I ./includes
INCLUDE		=	./includes
INCLUDEL	=	-I ./$(LIBDIR)/
INCLUDES_VISU	=	-I ~/usr/local/includes/ 

OBJDIR		= 	objs

OBJDIR_ALGO	=	objs/algo

SRCDIR_ALGO	=	srcs/algo

SRC_ALGO	=	main.c\
				parsing.c\
				add_info.c\
				add_ants.c\
				add_rooms.c\
				add_links.c\
				reader.c\
				created_map.c\
				created_hash.c\
				created_path.c\
				path_creation_utils.c\
				path_creation_utils_2.c\
				path_creation_utils_3.c\
				visu.c\
				design.c\
				event.c\
				image.c\
				view_map.c\
				move_ants.c\
				room_cre_utils.c\
				tool_move.c\
				move_ants_utils.c\

OBJ_ALGO	=	$(SRC_ALGO:.c=.o)

SRCS_ALGO	=	$(addprefix $(SRCDIR_ALGO)/, $(SRC_ALGO))
OBJS_ALGO	=	$(addprefix $(OBJDIR_ALGO)/, $(SRC_ALGO:.c=.o))

all: directory $(NAME) $(VISU)

$(NAME): $(OBJDIR_ALGO) $(LIB) $(OBJS_ALGO) $(INCLUDE)
	@$(CC) $(FLAGS) srcs/algo/libmlx.a $(LIB) $(LIB_VISU)  -o $@ $(OBJS_ALGO) $(LIBLINK)

# $(VISU): $(OBJDIR_VISU) $(LIB) $(OBJS_VISU) $(INCLUDE)
# 	cc  $(LIB) $(LIB_VISU) -o $@ $(OBJS_VISU) 

$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR_ALGO)/%.o: $(SRCDIR_ALGO)/%.c
	gcc $(FLAGS) -c $^ -o $@ $(INCLUDES) $(INCLUDEL)

$(OBJDIR_VISU)/%.o: $(SRCDIR_VISU)/%.c
	gcc $(FLAGS) -c $^ -o $@ $(INCLUDES) $(INCLUDES_VISU)

directory: $(OBJDIR) $(OBJDIR_ALGO) $(OBJDIR_VISU)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR_ALGO):
	@mkdir -p $(OBJDIR_ALGO)

$(OBJDIR_VISU):
	@mkdir -p $(OBJDIR_VISU)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJS_ALGO)
	@make -C $(LIBDIR) clean
	@rm -rf $(OBJDIR_ALGO)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(VISU)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: clean all re fclean directory
