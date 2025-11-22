/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_textures(t_mlx *mlx)
{
	char	*texture_paths[4];
	int		i;

	texture_paths[0] = mlx->game_map->texture_north;
	texture_paths[1] = mlx->game_map->texture_south;
	texture_paths[2] = mlx->game_map->texture_east;
	texture_paths[3] = mlx->game_map->texture_west;
	i = 0;
	while (i < 4)
	{
		mlx->textures[i] = mlx_xpm_file_to_image(mlx->mlx_ptr,
				texture_paths[i], &mlx->texture_width[i],
				&mlx->texture_height[i]);
		if (!mlx->textures[i])
		{
			printf("Error: Failed to load texture %s\n", texture_paths[i]);
			exit(EXIT_FAILURE);
		}
		mlx->texture_data[i] = mlx_get_data_addr(mlx->textures[i],
				&mlx->tex_bits_per_pixel[i], &mlx->tex_line_length[i],
				&mlx->tex_endian[i]);
		i++;
	}
}

void	put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < mlx->win_width && y >= 0 && y < mlx->win_height)
	{
		dst = mlx->img_data + (y * mlx->line_length + x
				* (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_texture_color(t_mlx *mlx, int tex_num, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= mlx->texture_width[tex_num]
		|| tex_y < 0 || tex_y >= mlx->texture_height[tex_num])
		return (0);
	pixel = mlx->texture_data[tex_num]
		+ (tex_y * mlx->tex_line_length[tex_num] + tex_x
		* (mlx->tex_bits_per_pixel[tex_num] / 8));
	return (*(unsigned int *)pixel);
}
