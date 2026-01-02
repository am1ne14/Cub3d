NAME    = cub3D
CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror

SRC     = src/main.c \
          src/game_loop.c \
          src/parsing/parser.c \
          src/parsing/rgb_utils.c \
          src/parsing/config_parsing.c \
          src/parsing/config_textures.c \
          src/parsing/config_textures_utils.c \
          src/parsing/config_colors.c \
          src/parsing/config_utils.c \
          src/parsing/config_check.c \
          src/parsing/trim_utils.c \
          src/parsing/parse_cleanup.c \
          src/parsing/parsing_map_init.c \
          src/parsing/map_verification.c \
          src/parsing/map_validation_utils.c \
          src/parsing/map_loading.c \
          src/init_data/init_mlx.c \
          src/init_data/init_game_map.c \
          src/init_data/texture_utils.c \
          src/init_data/player_init.c \
          src/init_data/rendering.c \
          src/key_hooks.c \
          src/raycasting.c \
          src/ray_calculation.c \
          src/player_movement.c \
          src/player_rotation.c

SRCG    = get_next_line/get_next_line.c \
          get_next_line/get_next_line_utils.c

OBJ     = $(SRC:.c=.o)
OBJG    = $(SRCG:.c=.o)

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = /usr/include/minilibx-linux

INCLUDES  = -Iincludes -I$(LIBFT_DIR) -I$(MINILIBX_DIR)

LIBS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ) $(OBJG) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(OBJG) $(LIBFT) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ) $(OBJG)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
