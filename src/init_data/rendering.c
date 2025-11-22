/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_ceiling(t_mlx *mlx, int x, int y)
{
	int	color;

	color = (mlx->game_map->ceiling_rgb.red << 16)
		| (mlx->game_map->ceiling_rgb.green << 8)
		| mlx->game_map->ceiling_rgb.blue;
	put_pixel_to_image(mlx, x, y, color);
}

void	draw_floor(t_mlx *mlx, int x, int y)
{
	int	color;

	color = (mlx->game_map->floor_rgb.red << 16)
		| (mlx->game_map->floor_rgb.green << 8)
		| mlx->game_map->floor_rgb.blue;
	put_pixel_to_image(mlx, x, y, color);
}

void	render_background(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->win_height)
	{
		x = 0;
		while (x < mlx->win_width)
		{
			if (y < mlx->win_height / 2)
				draw_ceiling(mlx, x, y);
			else
				draw_floor(mlx, x, y);
			x++;
		}
		y++;
	}
}

int	render_frame(t_mlx *mlx)
{
	render_background(mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (0);
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
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_width,
			mlx->win_height, "cub3D");
	if (!mlx->win_ptr)
		exit(EXIT_FAILURE);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_width,
			mlx->win_height);
	if (!mlx->img_ptr)
		exit(EXIT_FAILURE);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 17, 1L << 17, close_window, mlx);
	mlx_loop_hook(mlx->mlx_ptr, render_frame, mlx);
}
