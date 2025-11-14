#include "../../includes/cub3d.h"

void	cleanup_game_map(t_game_map *game_map)
{
	int	i;
	if (game_map->map_grid)
	{
		i = 0;
		while (i < game_map->map_height)
		{
			if (game_map->map_grid[i])
				free(game_map->map_grid[i]);
			i++;
		}
		free(game_map->map_grid);
	}
	if (game_map->texture_north)
		free(game_map->texture_north);
	if (game_map->texture_south)
		free(game_map->texture_south);
	if (game_map->texture_west)
		free(game_map->texture_west);
	if (game_map->texture_east)
		free(game_map->texture_east);
}

char	*trim_line_spaces(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int	len;
	int	i;

	if (!str)
		return (NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

int	convert_rgb_string(char *rgb_str, t_rgb_color *color)
{
	char	**rgb_parts;
	int	values[3];
	int	i;
	int	j;

	rgb_parts = ft_split(rgb_str, ',');
	if (!rgb_parts)
		return (0);
	i = 0;
	while (rgb_parts[i] && i < 3)
		i++;
	if (i != 3 || rgb_parts[3])
	{
		i = 0;
		while (rgb_parts[i])
			free(rgb_parts[i++]);
		free(rgb_parts);
		display_parse_error("RGB color must have exactly 3 values");
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		values[i] = ft_atoi(rgb_parts[i]);
		if (values[i] < 0 || values[i] > 255)
		{
			j = 0;
			while (rgb_parts[j])
				free(rgb_parts[j++]);
			free(rgb_parts);
			display_parse_error("RGB values must be between 0 and 255");
			return (0);
		}
		i++;
	}
	color->red = values[0];
	color->green = values[1];
	color->blue = values[2];
	i = 0;
	while (rgb_parts[i])
		free(rgb_parts[i++]);
	free(rgb_parts);
	return (1);
}

void	display_parse_error(char *message)
{
	printf("Error: %s\n", message);
}

int	check_all_configs_set(t_game_map *game_map)
{
	return (game_map->config_count >= 6 &&
			game_map->texture_north && game_map->texture_south &&
			game_map->texture_west && game_map->texture_east &&
			game_map->floor_rgb.red >= 0 && game_map->ceiling_rgb.red >= 0);
}