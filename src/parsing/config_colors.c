#include "../../includes/cub3d.h"

static int	store_color_config(char *identifier, t_rgb_color *color,
	char *rgb_str, t_game_map *game_map)
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

static int	process_color_identifier(char **parts, t_game_map *game_map)
{
	int	result;

	if (ft_strncmp(parts[0], "F", 1) == 0)
		result = store_color_config(parts[0], &game_map->floor_rgb,
				parts[1], game_map);
	else if (ft_strncmp(parts[0], "C", 1) == 0)
		result = store_color_config(parts[0], &game_map->ceiling_rgb,
				parts[1], game_map);
	else
	{
		display_parse_error("Invalid color identifier - must be F or C");
		result = 0;
	}
	return (result);
}

int	handle_color_config(char *line, t_game_map *game_map)
{
	char	**parts;
	int		result;

	parts = ft_split(line, ' ');
	if (!validate_color_parts(parts))
		return (0);
	result = process_color_identifier(parts, game_map);
	free_split_parts(parts);
	return (result);
}
