/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:37:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/19 23:37:01 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int	is_player_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_player_position(t_game_map *game_map, int x, int y, char direction)
{
	if (game_map->player_count > 0)
	{
		display_parse_error("Multiple players found in map");
		return (0);
	}
	game_map->player.pos_x = (double)x + 0.5;
	game_map->player.pos_y = (double)y + 0.5;
	game_map->player.facing = direction;
	game_map->player_count++;
	return (1);
}

int	validate_map_line(char *line, t_game_map *game_map, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!check_valid_map_character(line[x]))
		{
			display_parse_error("Invalid character in map");
			return (0);
		}
		if (is_player_character(line[x]))
		{
			if (!find_player_position(game_map, x, y, line[x]))
				return (0);
			line[x] = '0';
		}
		x++;
	}
	return (1);
}

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
	while ((original_line = get_next_line(fd)) != NULL)
	{
		if (!process_map_line(original_line, game_map, &map_capacity))
			return (0);
	}
	return (1);
}

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
		display_parse_error("Map must contain exactly one player starting position");
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

int	check_map(char *file)
{
	t_game_map game_map;

	initialize_game_map(&game_map);
	if (!process_config_file(file, &game_map))
	{
		cleanup_game_map(&game_map);
		return (0);
	}
	if (!validate_game_map(&game_map))
	{
		cleanup_game_map(&game_map);
		return (0);
	}
	cleanup_game_map(&game_map);
	return (1);
}
