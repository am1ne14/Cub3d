/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:21:53 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:49:43 by bamdjar          ###   ########.fr       */
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

static int	find_player_position(t_game_map *game_map, int x, int y,
	char direction)
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

int	check_map(char *file)
{
	t_game_map	game_map;

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
