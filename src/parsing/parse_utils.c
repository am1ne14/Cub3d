/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:37:19 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/19 23:37:21 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*find_trim_start(char *str)
{
	char	*start;

	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	return (start);
}

static char	*find_trim_end(char *start)
{
	char	*end;

	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		end--;
	return (end);
}

static char	*copy_trimmed_string(char *start, int len)
{
	char	*result;
	int		i;

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

char	*trim_line_spaces(char *str)
{
	char	*start;
	char	*end;
	int		len;

	if (!str)
		return (NULL);
	start = find_trim_start(str);
	if (*start == '\0')
		return (ft_strdup(""));
	end = find_trim_end(start);
	len = end - start + 1;
	return (copy_trimmed_string(start, len));
}

static int	count_rgb_parts(char **rgb_parts)
{
	int	i;

	i = 0;
	while (rgb_parts[i] && i < 3)
		i++;
	return (i);
}

static void	free_rgb_parts(char **rgb_parts)
{
	int	i;

	i = 0;
	while (rgb_parts[i])
		free(rgb_parts[i++]);
	free(rgb_parts);
}

static int	validate_rgb_values(char **rgb_parts, int *values)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		values[i] = ft_atoi(rgb_parts[i]);
		if (values[i] < 0 || values[i] > 255)
		{
			free_rgb_parts(rgb_parts);
			display_parse_error("RGB values must be between 0 and 255");
			return (0);
		}
		i++;
	}
	return (1);
}

int	convert_rgb_string(char *rgb_str, t_rgb_color *color)
{
	char	**rgb_parts;
	int		values[3];
	int		part_count;

	rgb_parts = ft_split(rgb_str, ',');
	if (!rgb_parts)
		return (0);
	part_count = count_rgb_parts(rgb_parts);
	if (part_count != 3 || rgb_parts[3])
	{
		free_rgb_parts(rgb_parts);
		display_parse_error("RGB color must have exactly 3 values");
		return (0);
	}
	if (!validate_rgb_values(rgb_parts, values))
		return (0);
	color->red = values[0];
	color->green = values[1];
	color->blue = values[2];
	free_rgb_parts(rgb_parts);
	return (1);
}

void	display_parse_error(char *message)
{
	printf("Error: %s\n", message);
}

int	check_all_configs_set(t_game_map *game_map)
{
	return (game_map->config_count >= 6
		&& game_map->texture_north && game_map->texture_south
		&& game_map->texture_west && game_map->texture_east
		&& game_map->floor_rgb.red >= 0 && game_map->ceiling_rgb.red >= 0);
}