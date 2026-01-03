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

static char	*dup_line_keep_spaces(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] && line[len] != '\n' && line[len] != '\r')
		len++;
	return (ft_substr(line, 0, len));
}

static int	init_map_grid(t_game_map *game_map, char *map_line)
{
	game_map->map_grid = malloc(sizeof(char *) * 10);
	if (!game_map->map_grid)
	{
		free(map_line);
		return (0);
	}
	if (!validate_map_line(map_line, game_map, 0))
	{
		free(map_line);
		return (0);
	}
	game_map->map_grid[0] = map_line;
	game_map->map_height = 1;
	game_map->map_width = ft_strlen(map_line);
	return (1);
}

int	handle_map_start(char *line, t_game_map *game_map, int fd)
{
	char	*raw_line;

	if (!check_all_configs_set(game_map))
	{
		display_parse_error("Missing config parameters");
		free(line);
		return (0);
	}
	raw_line = dup_line_keep_spaces(line);
	free(line);
	if (!raw_line)
	{
		return (0);
	}
	if (ft_strlen(raw_line) == 0)
	{
		display_parse_error("Empty map line");
		free(raw_line);
		return (0);
	}
	if (!init_map_grid(game_map, raw_line))
		return (0);
	if (!process_map_data(fd, game_map))
		return (0);
	return (1);
}
