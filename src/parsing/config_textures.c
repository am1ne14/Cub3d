#include "../../includes/cub3d.h"

static int	store_north_texture(char *path, t_game_map *game_map)
{
	if (game_map->texture_north)
	{
		display_parse_error("Duplicate North texture");
		return (0);
	}
	game_map->texture_north = ft_strdup(path);
	return (1);
}

static int	store_south_texture(char *path, t_game_map *game_map)
{
	if (game_map->texture_south)
	{
		display_parse_error("Duplicate South texture");
		return (0);
	}
	game_map->texture_south = ft_strdup(path);
	return (1);
}

static int	store_west_texture(char *path, t_game_map *game_map)
{
	if (game_map->texture_west)
	{
		display_parse_error("Duplicate West texture");
		return (0);
	}
	game_map->texture_west = ft_strdup(path);
	return (1);
}

static int	store_east_texture(char *path, t_game_map *game_map)
{
	if (game_map->texture_east)
	{
		display_parse_error("Duplicate East texture");
		return (0);
	}
	game_map->texture_east = ft_strdup(path);
	return (1);
}

int	store_texture_path(char *identifier, char *path, t_game_map *game_map)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
	{
		if (!store_north_texture(path, game_map))
			return (0);
	}
	else if (ft_strncmp(identifier, "SO", 2) == 0)
	{
		if (!store_south_texture(path, game_map))
			return (0);
	}
	else if (ft_strncmp(identifier, "WE", 2) == 0)
	{
		if (!store_west_texture(path, game_map))
			return (0);
	}
	else if (ft_strncmp(identifier, "EA", 2) == 0)
	{
		if (!store_east_texture(path, game_map))
			return (0);
	}
	else
		return (0);
	game_map->config_count++;
	return (1);
}
