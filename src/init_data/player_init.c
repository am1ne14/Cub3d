/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@github.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_north(t_mlx *mlx)
{
	mlx->player.dir_x = 0.0;
	mlx->player.dir_y = -1.0;
	mlx->player.plane_x = 0.66;
	mlx->player.plane_y = 0.0;
}

void	init_player_south(t_mlx *mlx)
{
	mlx->player.dir_x = 0.0;
	mlx->player.dir_y = 1.0;
	mlx->player.plane_x = -0.66;
	mlx->player.plane_y = 0.0;
}

void	init_player_east(t_mlx *mlx)
{
	mlx->player.dir_x = 1.0;
	mlx->player.dir_y = 0.0;
	mlx->player.plane_x = 0.0;
	mlx->player.plane_y = 0.66;
}

void	init_player_west(t_mlx *mlx)
{
	mlx->player.dir_x = -1.0;
	mlx->player.dir_y = 0.0;
	mlx->player.plane_x = 0.0;
	mlx->player.plane_y = -0.66;
}

void	init_player(t_mlx *mlx, t_game_map *game_map)
{
	mlx->player.pos_x = game_map->player.pos_x;
	mlx->player.pos_y = game_map->player.pos_y;
	if (game_map->player.facing == 'N')
		init_player_north(mlx);
	else if (game_map->player.facing == 'S')
		init_player_south(mlx);
	else if (game_map->player.facing == 'E')
		init_player_east(mlx);
	else if (game_map->player.facing == 'W')
		init_player_west(mlx);
}
