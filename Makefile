NAME = cub3d

SRCS	=	src/check_file.c	\
			src/check_map.c	\
			src/create_map.c	\
			src/destroy.c		\
			src/draw.c			\
			src/error.c			\
			src/ft_atoi.c		\
			src/ft_split.c		\
			src/ft_strchr.c		\
			src/ft_strcmp.c		\
			src/ft_strdup.c		\
			src/ft_strlcpy.c	\
			src/ft_strlen.c		\
			src/ft_substr.c		\
			src/get_next_line_utils.c	\
			src/get_next_line.c	\
			src/init_data.c		\
			src/main.c			\
			src/next_frame.c	\


OBJS = $(SRCS:%.c=%.o)

CC = cc
# CFLAGS = -Wall -Wextra -Werror -I include
CFLAGS = -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJS) $(M_OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

bonus:	$(OBJS) $(B_OBJS)
	make WITH_BONUS=1

re: fclean all

.PHONY: all clean fclean bonus re