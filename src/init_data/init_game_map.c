#include "../../includes/cub3d.h"

void	initialize_game_map(t_game_map *game_map)
{
	game_map->map_grid = NULL;
	game_map->map_width = 0;
	game_map->map_height = 0;
	game_map->texture_north = NULL;
	game_map->texture_south = NULL;
	game_map->texture_west = NULL;
	game_map->texture_east = NULL;
	game_map->floor_rgb.red = -1;
	game_map->floor_rgb.green = -1;
	game_map->floor_rgb.blue = -1;
	game_map->ceiling_rgb.red = -1;
	game_map->ceiling_rgb.green = -1;
	game_map->ceiling_rgb.blue = -1;
	game_map->player.pos_x = -1;
	game_map->player.pos_y = -1;
	game_map->player.facing = '\0';
	game_map->config_count = 0;
	game_map->player_count = 0;
}
