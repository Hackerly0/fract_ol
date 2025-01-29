NAME = fract_ol
SRCS = main.c mandelbrot.c julia.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OBJS = $(SRCS: .c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -g -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
fclean:
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
