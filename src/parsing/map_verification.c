#include "../../includes/cub3d.h"

static int	verify_first_row(t_game_map *game_map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (x < (int)ft_strlen(game_map->map_grid[y]))
	{
		if (game_map->map_grid[y][x] != '1')
		{
			display_parse_error("First row must be all walls");
			return (0);
		}
		x++;
	}
	return (1);
}

static int	verify_last_row(t_game_map *game_map)
{
	int	x;
	int	y;

	y = game_map->map_height - 1;
	x = 0;
	while (x < (int)ft_strlen(game_map->map_grid[y]))
	{
		if (game_map->map_grid[y][x] != '1')
		{
			display_parse_error("Last row must be all walls");
			return (0);
		}
		x++;
	}
	return (1);
}

static int	verify_side_walls(t_game_map *game_map)
{
	int	y;
	int	len;

	y = 0;
	while (y < game_map->map_height)
	{
		if (game_map->map_grid[y][0] != '1')
		{
			display_parse_error("First column must be walls");
			return (0);
		}
		len = ft_strlen(game_map->map_grid[y]);
		if (len > 0 && game_map->map_grid[y][len - 1] != '1')
		{
			display_parse_error("Last column must be walls");
			return (0);
		}
		y++;
	}
	return (1);
}

int	verify_map_boundaries(t_game_map *game_map)
{
	if (!verify_first_row(game_map))
		return (0);
	if (!verify_last_row(game_map))
		return (0);
	if (!verify_side_walls(game_map))
		return (0);
	return (1);
}

int	validate_game_map(t_game_map *game_map)
{
	if (game_map->player_count != 1)
	{
		display_parse_error("Map must contain exactly one "\
			"player starting position");
		return (0);
	}
	if (game_map->map_height < 3)
	{
		display_parse_error("Map is too small");
		return (0);
	}
	if (!verify_map_boundaries(game_map))
	{
		display_parse_error("Map is not properly enclosed by walls");
		return (0);
	}
	return (1);
}
