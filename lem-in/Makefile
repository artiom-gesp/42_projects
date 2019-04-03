CC			=	gcc
NAME		=	lem-in
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

SRC_ALGO	=	add_info.c \
				add_links_matrice.c \
				add_rooms.c \
				created_hash.c \
				created_path.c \
				design.c \
				event.c \
				image.c \
				main.c \
				move_ants.c \
				move_ants_utils.c \
				path_creation_utils.c \
				path_creation_utils_2.c \
				path_creation_utils_3.c \
				reader.c \
				room_cre_utils.c \
				solve.c \
				tool_move.c \
				view_map.c \
				visu.c\
				add_ants.c\

OBJ_ALGO	=	$(SRC_ALGO:.c=.o)

SRCS_ALGO	=	$(addprefix $(SRCDIR_ALGO)/, $(SRC_ALGO))
OBJS_ALGO	=	$(addprefix $(OBJDIR_ALGO)/, $(SRC_ALGO:.c=.o))

all: directory $(NAME) 

$(NAME): $(OBJDIR_ALGO) $(LIB) $(OBJS_ALGO) $(INCLUDE)
	@$(CC) $(FLAGS) srcs/algo/libmlx.a $(LIB) $(LIB_VISU)  -o $@ $(OBJS_ALGO) $(LIBLINK)

$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR_ALGO)/%.o: $(SRCDIR_ALGO)/%.c
	gcc $(FLAGS) -c $^ -o $@ $(INCLUDES) $(INCLUDEL)

directory: $(OBJDIR) $(OBJDIR_ALGO)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR_ALGO):
	@mkdir -p $(OBJDIR_ALGO)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJS_ALGO)
	@make -C $(LIBDIR) clean
	@rm -rf $(OBJDIR_ALGO)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: clean all re fclean directory
