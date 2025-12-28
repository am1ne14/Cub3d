/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:31:21 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	game_loop(t_mlx *mlx)
{
	if (mlx->key_w)
		move_player_forward(mlx);
	if (mlx->key_s)
		move_player_backward(mlx);
	if (mlx->key_a)
		move_player_left(mlx);
	if (mlx->key_d)
		move_player_right(mlx);
	if (mlx->key_left)
		rotate_player_left(mlx);
	if (mlx->key_right)
		rotate_player_right(mlx);
	render_frame(mlx);
	return (0);
}

static void	init_keys(t_mlx *mlx)
{
	mlx->key_w = 0;
	mlx->key_s = 0;
	mlx->key_a = 0;
	mlx->key_d = 0;
	mlx->key_left = 0;
	mlx->key_right = 0;
}

static void	init_window_and_image(t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_width,
			mlx->win_height, "cub3D");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_width,
			mlx->win_height);
	if (!mlx->img_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(EXIT_FAILURE);
	}
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
}

void	init_mlx(t_mlx *mlx, t_game_map *game_map)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(EXIT_FAILURE);
	mlx->win_width = SCREEN_WIDTH;
	mlx->win_height = SCREEN_HEIGHT;
	mlx->game_map = game_map;
	load_textures(mlx);
	init_player(mlx, game_map);
	init_keys(mlx);
	init_window_and_image(mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win_ptr, 17, 1L << 17, close_window, mlx);
	mlx_loop_hook(mlx->mlx_ptr, game_loop, mlx);
}
