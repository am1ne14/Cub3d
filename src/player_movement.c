/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:38:50 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/26 14:38:53 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= mlx->game_map->map_width
		|| map_y < 0 || map_y >= mlx->game_map->map_height)
		return (1);
	return (mlx->game_map->map_grid[map_y][map_x] == '1');
}

void	move_player_forward(t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player.pos_x + mlx->player.dir_x * MOVE_SPEED;
	new_y = mlx->player.pos_y + mlx->player.dir_y * MOVE_SPEED;
	if (!is_wall(mlx, new_x, mlx->player.pos_y))
		mlx->player.pos_x = new_x;
	if (!is_wall(mlx, mlx->player.pos_x, new_y))
		mlx->player.pos_y = new_y;
}

void	move_player_backward(t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player.pos_x - mlx->player.dir_x * MOVE_SPEED;
	new_y = mlx->player.pos_y - mlx->player.dir_y * MOVE_SPEED;
	if (!is_wall(mlx, new_x, mlx->player.pos_y))
		mlx->player.pos_x = new_x;
	if (!is_wall(mlx, mlx->player.pos_x, new_y))
		mlx->player.pos_y = new_y;
}

void	move_player_left(t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player.pos_x - mlx->player.plane_x * MOVE_SPEED;
	new_y = mlx->player.pos_y - mlx->player.plane_y * MOVE_SPEED;
	if (!is_wall(mlx, new_x, mlx->player.pos_y))
		mlx->player.pos_x = new_x;
	if (!is_wall(mlx, mlx->player.pos_x, new_y))
		mlx->player.pos_y = new_y;
}

void	move_player_right(t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player.pos_x + mlx->player.plane_x * MOVE_SPEED;
	new_y = mlx->player.pos_y + mlx->player.plane_y * MOVE_SPEED;
	if (!is_wall(mlx, new_x, mlx->player.pos_y))
		mlx->player.pos_x = new_x;
	if (!is_wall(mlx, mlx->player.pos_x, new_y))
		mlx->player.pos_y = new_y;
}
