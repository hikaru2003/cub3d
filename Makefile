NAME = cub3d

SRCS	=	check_file.c	\
			check_map.c	\
			create_map.c	\
			destroy.c		\
			draw.c			\
			error.c			\
			get_next_line_utils.c	\
			get_next_line.c	\
			init_data.c		\
			main.c			\
			next_frame.c	\

INCLUDE_DIR = ./include
SRCDIR = ./srcs/
OBJDIR = ./obj/

MLX_DIR = ./mlx/

LIBFT_DIR = ./libft/
LIBFT_A = $(LIBFT_DIR)libft.a

OBJS = $(SRCS:%.c=$(OBJDIR)%.o)

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -I include
CFLAGS = -I include #-g -fsanitize=address

MLX_FLAG = -lmlx -framework OpenGL -framework AppKit

all: $(LIBFT_A) $(OBJDIR) $(NAME)

$(NAME): $(MLX_DIR) $(LIBFT_A) $(OBJDIR) $(OBJS)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -Lmlx $(MLX_FLAG) -o $(NAME) $(LIBFT_A) $(OBJS)
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT_A):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
