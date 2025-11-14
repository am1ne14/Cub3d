#include "../../includes/cub3d.h"

static int	store_texture_path(char *identifier, char *path, t_game_map *game_map)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
	{
		if (game_map->texture_north)
		{
			display_parse_error("Duplicate North texture");
			return (0);
		}
		game_map->texture_north = ft_strdup(path);
	}
	else if (ft_strncmp(identifier, "SO", 2) == 0)
	{
		if (game_map->texture_south)
		{
			display_parse_error("Duplicate South texture");
			return (0);
		}
		game_map->texture_south = ft_strdup(path);
	}
	else if (ft_strncmp(identifier, "WE", 2) == 0)
	{
		if (game_map->texture_west)
		{
			display_parse_error("Duplicate West texture");
			return (0);
		}
		game_map->texture_west = ft_strdup(path);
	}
	else if (ft_strncmp(identifier, "EA", 2) == 0)
	{
		if (game_map->texture_east)
		{
			display_parse_error("Duplicate East texture");
			return (0);
		}
		game_map->texture_east = ft_strdup(path);
	}
	else
		return (0);
	game_map->config_count++;
	return (1);
}

int	handle_texture_config(char *line, t_game_map *game_map)
{
	char	**parts;
	int	result;
	int	i;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		display_parse_error("Invalid texture format - should be: [NO|SO|WE|EA] <path>");
		if (parts)
		{
			i = 0;
			while (parts[i])
				free(parts[i++]);
			free(parts);
		}
		return (0);
	}
	result = store_texture_path(parts[0], parts[1], game_map);
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (result);
}

static int	store_color_config(char *identifier, t_rgb_color *color, char *rgb_str, t_game_map *game_map)
{
	if (color->red >= 0)
	{
		if (ft_strncmp(identifier, "F", 1) == 0)
			display_parse_error("Duplicate Floor color");
		else
			display_parse_error("Duplicate Ceiling color");
		return (0);
	}
	if (!convert_rgb_string(rgb_str, color))
		return (0);
	game_map->config_count++;
	return (1);
}

int	handle_color_config(char *line, t_game_map *game_map)
{
	char	**parts;
	int	result;
	int	i;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		display_parse_error("Invalid color format - should be: [F|C] R,G,B");
		if (parts)
		{
			i = 0;
			while (parts[i])
				free(parts[i++]);
			free(parts);
		}
		return (0);
	}
	if (ft_strncmp(parts[0], "F", 1) == 0)
		result = store_color_config(parts[0], &game_map->floor_rgb, parts[1], game_map);
	else if (ft_strncmp(parts[0], "C", 1) == 0)
		result = store_color_config(parts[0], &game_map->ceiling_rgb, parts[1], game_map);
	else
	{
		display_parse_error("Invalid color identifier - must be F or C");
		result = 0;
	}
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (result);
}
