/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@github.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player_left(t_mlx *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(ROT_SPEED)
		- mlx->player.dir_y * sin(ROT_SPEED);
	mlx->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ mlx->player.dir_y * cos(ROT_SPEED);
	old_plane_x = mlx->player.plane_x;
	mlx->player.plane_x = mlx->player.plane_x * cos(ROT_SPEED)
		- mlx->player.plane_y * sin(ROT_SPEED);
	mlx->player.plane_y = old_plane_x * sin(ROT_SPEED)
		+ mlx->player.plane_y * cos(ROT_SPEED);
}

void	rotate_player_right(t_mlx *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(-ROT_SPEED)
		- mlx->player.dir_y * sin(-ROT_SPEED);
	mlx->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ mlx->player.dir_y * cos(-ROT_SPEED);
	old_plane_x = mlx->player.plane_x;
	mlx->player.plane_x = mlx->player.plane_x * cos(-ROT_SPEED)
		- mlx->player.plane_y * sin(-ROT_SPEED);
	mlx->player.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ mlx->player.plane_y * cos(-ROT_SPEED);
}
