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

static int	is_only_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	add_map_line(char *line, t_game_map *game_map, int *capacity)
{
	char	**temp_grid;
	int		i;

	if (game_map->map_height >= *capacity)
	{
		*capacity *= 2;
		temp_grid = malloc(sizeof(char *) * (*capacity));
		if (!temp_grid)
			return (free(line), 0);
		i = 0;
		while (i < game_map->map_height)
		{
			temp_grid[i] = game_map->map_grid[i];
			i++;
		}
		free(game_map->map_grid);
		game_map->map_grid = temp_grid;
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
	size_t	len;

	len = 0;
	while (original_line[len] && original_line[len] != '\n'
		&& original_line[len] != '\r')
		len++;
	line = ft_substr(original_line, 0, len);
	free(original_line);
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (display_parse_error("Empty line inside map"), free(line), 0);
	if (!validate_map_line(line, game_map, game_map->map_height))
		return (free(line), 0);
	return (add_map_line(line, game_map, capacity));
}

static int	skip_trailing_lines(int fd, char *line)
{
	while (line && is_only_whitespace(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (1);
	free(line);
	display_parse_error("Invalid content after map");
	return (0);
}

int	process_map_data(int fd, t_game_map *game_map)
{
	char	*line;
	int		capacity;

	capacity = 10;
	if (!game_map->map_grid)
	{
		game_map->map_grid = malloc(sizeof(char *) * capacity);
		if (!game_map->map_grid)
			return (0);
		game_map->map_height = 0;
		game_map->map_width = 0;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (game_map->map_height > 0 && is_only_whitespace(line))
			return (skip_trailing_lines(fd, line));
		if (!process_map_line(line, game_map, &capacity))
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}
