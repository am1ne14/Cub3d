/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:40:35 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/26 14:40:42 by mohel-am         ###   ########.fr       */
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
