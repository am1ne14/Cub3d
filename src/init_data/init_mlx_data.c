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

static void	init_player_north(t_mlx *mlx)
{
	mlx->player.dir_x = 0.0;
	mlx->player.dir_y = -1.0;
	mlx->player.plane_x = 0.66;
	mlx->player.plane_y = 0.0;
}

static void	init_player_south(t_mlx *mlx)
{
	mlx->player.dir_x = 0.0;
	mlx->player.dir_y = 1.0;
	mlx->player.plane_x = -0.66;
	mlx->player.plane_y = 0.0;
}

static void	init_player_east(t_mlx *mlx)
{
	mlx->player.dir_x = 1.0;
	mlx->player.dir_y = 0.0;
	mlx->player.plane_x = 0.0;
	mlx->player.plane_y = 0.66;
}

static void	init_player_west(t_mlx *mlx)
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

static void	draw_ceiling(t_mlx *mlx, int x, int y)
{
	int	color;

	color = (mlx->game_map->ceiling_rgb.red << 16)
		| (mlx->game_map->ceiling_rgb.green << 8)
		| mlx->game_map->ceiling_rgb.blue;
	put_pixel_to_image(mlx, x, y, color);
}

static void	draw_floor(t_mlx *mlx, int x, int y)
{
	int	color;

	color = (mlx->game_map->floor_rgb.red << 16)
		| (mlx->game_map->floor_rgb.green << 8)
		| mlx->game_map->floor_rgb.blue;
	put_pixel_to_image(mlx, x, y, color);
}

static void	render_background(t_mlx *mlx)
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