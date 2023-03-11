#create a makefile to compile source files into an executable called cub3d

NAME = cub3d

SRCS = cub3d.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

.%c.%o: cub3d.h
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	cd libft && make
	cd ..
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	cd libft && make fclean
	cd ..
	$(RM) $(NAME)

re: fclean all

