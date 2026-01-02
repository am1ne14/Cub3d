/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 00:00:00 by bamdjar           #+#    #+#             */
/*   Updated: 2026/01/02 00:00:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	store_player_position(t_game_map *game_map, int x, int y, char c)
{
	if (game_map->player_count > 0)
	{
		display_parse_error("Multiple player positions found");
		return (0);
	}
	game_map->player_count = 1;
	game_map->player.pos_x = x + 0.5;
	game_map->player.pos_y = y + 0.5;
	game_map->player.facing = c;
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
		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'E' || line[x] == 'W')
		{
			if (!store_player_position(game_map, x, y, line[x]))
				return (0);
			line[x] = '0';
		}
		x++;
	}
	return (1);
}
