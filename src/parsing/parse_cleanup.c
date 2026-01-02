/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:58:21 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:51:44 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display_parse_error(char *message)
{
	printf("Error: %s\n", message);
}

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
