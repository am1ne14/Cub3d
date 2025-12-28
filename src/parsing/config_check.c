/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:49:06 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:49:29 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_all_configs_set(t_game_map *game_map)
{
	return (game_map->config_count >= 6
		&& game_map->texture_north && game_map->texture_south
		&& game_map->texture_west && game_map->texture_east
		&& game_map->floor_rgb.red >= 0 && game_map->ceiling_rgb.red >= 0);
}
