/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:39:03 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/26 14:39:08 by mohel-am         ###   ########.fr       */
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
