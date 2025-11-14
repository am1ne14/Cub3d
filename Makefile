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
		  src/hooks/key_hooks.c \
		  src/rendering/raycasting.c \
		  src/movement/player_movement.c \

OBJ     = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a
INCLUDES  = -Iinclude -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
LIBS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINILIBX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
