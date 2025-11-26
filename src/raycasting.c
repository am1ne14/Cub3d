/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:36:48 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/19 23:36:50 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_vertical_line(t_mlx *mlx, int x, t_ray *ray)
{
	int				y;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;

	step = 1.0 * mlx->texture_height[ray->tex_num] / ray->line_height;
	tex_pos = (ray->draw_start - mlx->win_height / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (mlx->texture_height[ray->tex_num] - 1);
		tex_pos += step;
		color = get_texture_color(mlx, ray->tex_num, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel_to_image(mlx, x, y, color);
		y++;
	}
}

void	cast_rays(t_mlx *mlx)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < mlx->win_width)
	{
		init_ray(mlx, &ray, x);
		/*calculate_step_and_side_dist(mlx, &ray);
		perform_dda(mlx, &ray);
		calculate_wall_distance(mlx, &ray);
		calculate_texture_coordinates(mlx, &ray);
		draw_vertical_line(mlx, x, &ray);*/
		x++;
	}
}

