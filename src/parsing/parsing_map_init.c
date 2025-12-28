/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:58:35 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_map_grid(t_game_map *game_map, char *trimmed, int fd)
{
	game_map->map_grid = malloc(sizeof(char *) * 10);
	if (!game_map->map_grid)
	{
		free(trimmed);
		close(fd);
		return (0);
	}
	if (!validate_map_line(trimmed, game_map, 0))
	{
		free(trimmed);
		close(fd);
		return (0);
	}
	game_map->map_grid[0] = trimmed;
	game_map->map_height = 1;
	game_map->map_width = ft_strlen(trimmed);
	return (1);
}

static int	process_first_map_line(char *trimmed, t_game_map *game_map, int fd)
{
	if (trimmed && ft_strlen(trimmed) > 0)
	{
		if (!init_map_grid(game_map, trimmed, fd))
			return (0);
	}
	else
	{
		if (trimmed)
			free(trimmed);
	}
	return (1);
}

int	handle_map_start(char *line, t_game_map *game_map, int fd)
{
	char	*trimmed;

	if (!check_all_configs_set(game_map))
	{
		display_parse_error("Missing config parameters");
		free(line);
		close(fd);
		return (0);
	}
	trimmed = trim_line_spaces(line);
	free(line);
	if (!process_first_map_line(trimmed, game_map, fd))
		return (0);
	if (!process_map_data(fd, game_map))
	{
		close(fd);
		return (0);
	}
	return (1);
}
