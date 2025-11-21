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

static void	init_ray(t_mlx *mlx, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)mlx->win_width - 1;
	ray->ray_dir_x = mlx->player.dir_x + mlx->player.plane_x * ray->camera_x;
	ray->ray_dir_y = mlx->player.dir_y + mlx->player.plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player.pos_x;
	ray->map_y = (int)mlx->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	calculate_step_and_side_dist(t_mlx *mlx, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (mlx->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - mlx->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (mlx->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - mlx->player.pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_mlx *mlx, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (mlx->game_map->map_grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_distance(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - mlx->player.pos_x + 
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - mlx->player.pos_y + 
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(mlx->win_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + mlx->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + mlx->win_height / 2;
	if (ray->draw_end >= mlx->win_height)
		ray->draw_end = mlx->win_height - 1;
}

static void	calculate_texture_coordinates(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = mlx->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = mlx->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 2;
		else
			ray->tex_num = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
	ray->tex_x = (int)(ray->wall_x * (double)mlx->texture_width[ray->tex_num]);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || 
		(ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = mlx->texture_width[ray->tex_num] - ray->tex_x - 1;
}

void	draw_vertical_line(t_mlx *mlx, int x, t_ray *ray)
{
	int				y;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;

	step = 1.0 * mlx->texture_height[ray->tex_num] / ray->line_height;
	tex_pos = (ray->draw_start - mlx->win_height / 2 + ray->line_height / 2) * step;
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
		calculate_step_and_side_dist(mlx, &ray);
		perform_dda(mlx, &ray);
		calculate_wall_distance(mlx, &ray);
		calculate_texture_coordinates(mlx, &ray);
		draw_vertical_line(mlx, x, &ray);
		x++;
	}
}
