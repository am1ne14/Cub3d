/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:58:07 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	initialize_map_grid(t_game_map *game_map, int capacity)
{
	if (!game_map->map_grid)
	{
		game_map->map_grid = malloc(sizeof(char *) * capacity);
		if (!game_map->map_grid)
			return (0);
		game_map->map_height = 0;
		game_map->map_width = 0;
	}
	return (1);
}

static int	expand_map_grid(t_game_map *game_map, int *capacity)
{
	char	**temp_grid;
	int		i;

	*capacity *= 2;
	temp_grid = malloc(sizeof(char *) * (*capacity));
	if (!temp_grid)
		return (0);
	i = 0;
	while (i < game_map->map_height)
	{
		temp_grid[i] = game_map->map_grid[i];
		i++;
	}
	free(game_map->map_grid);
	game_map->map_grid = temp_grid;
	return (1);
}

static int	add_map_line(char *line, t_game_map *game_map, int *capacity)
{
	if (game_map->map_height >= *capacity)
	{
		if (!expand_map_grid(game_map, capacity))
		{
			free(line);
			return (0);
		}
	}
	game_map->map_grid[game_map->map_height] = line;
	if ((int)ft_strlen(line) > game_map->map_width)
		game_map->map_width = ft_strlen(line);
	game_map->map_height++;
	return (1);
}

static int	process_map_line(char *original_line, t_game_map *game_map,
	int *capacity)
{
	char	*line;

	line = trim_line_spaces(original_line);
	free(original_line);
	if (!line || ft_strlen(line) == 0)
	{
		if (line)
			free(line);
		return (1);
	}
	if (!validate_map_line(line, game_map, game_map->map_height))
	{
		free(line);
		return (0);
	}
	return (add_map_line(line, game_map, capacity));
}

int	process_map_data(int fd, t_game_map *game_map)
{
	char	*original_line;
	int		map_capacity;

	map_capacity = 10;
	if (!initialize_map_grid(game_map, map_capacity))
		return (0);
	original_line = get_next_line(fd);
	while (original_line != NULL)
	{
		if (!process_map_line(original_line, game_map, &map_capacity))
			return (0);
		original_line = get_next_line(fd);
	}
	return (1);
}
