NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC     = src/main.c \
          src/parsing/parser.c \
          src/parsing/check_map.c \
          src/parsing/parse_utils.c \
          src/parsing/config_handler.c \
          src/init_data/init_game_map.c \
          src/init_data/init_mlx_data.c \
          src/key_hooks.c \
          src/raycasting.c \
          src/player_movement.c

SRCG    = get_next_line/get_next_line.c \
          get_next_line/get_next_line_utils.c

OBJ     = $(SRC:.c=.o)
OBJG    = $(SRCG:.c=.o)

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = /usr/include/minilibx-linux

INCLUDES  = -Iinclude -I$(LIBFT_DIR) -I$(MINILIBX_DIR)

LIBS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ) $(OBJG) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(OBJG) $(LIBFT) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJ) $(OBJG)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
