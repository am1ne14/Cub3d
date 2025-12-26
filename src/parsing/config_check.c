#include "../../includes/cub3d.h"

int	check_all_configs_set(t_game_map *game_map)
{
	return (game_map->config_count >= 6
		&& game_map->texture_north && game_map->texture_south
		&& game_map->texture_west && game_map->texture_east
		&& game_map->floor_rgb.red >= 0 && game_map->ceiling_rgb.red >= 0);
}
