/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 02:31:34 by mtaybi            #+#    #+#             */
/*   Updated: 2025/11/19 23:17:36 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../includes/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define FOV 60
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef struct s_rgb_color
{
	int	red;
	int	green;
	int	blue;
}	t_rgb_color;

typedef struct s_player_pos
{
	double	pos_x;
	double	pos_y;
	char	facing;
}	t_player_pos;

typedef struct s_game_map
{
	char			**map_grid;
	int				map_width;
	int				map_height;
	char			*texture_north;
	char			*texture_south;
	char			*texture_west;
	char			*texture_east;
	t_rgb_color		floor_rgb;
	t_rgb_color		ceiling_rgb;
	t_player_pos	player;
	int				config_count;
	int				player_count;
}	t_game_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_num;
	int		tex_x;
}	t_ray;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
	void		*img_ptr;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
	t_game_map	*game_map;
	void		*textures[4];
	char		*texture_data[4];
	int			texture_width[4];
	int			texture_height[4];
	int			tex_bits_per_pixel[4];
	int			tex_line_length[4];
	int			tex_endian[4];
}	t_mlx;

/* Parsing functions */
int process_config_file(char *filename, t_game_map *game_map);
int handle_texture_config(char *line, t_game_map *game_map);
int handle_color_config(char *line, t_game_map *game_map);
int process_map_data(int fd, t_game_map *game_map);
int validate_game_map(t_game_map *game_map);
int check_valid_map_character(char c);
int verify_map_boundaries(t_game_map *game_map);
int validate_map_line(char *line, t_game_map *game_map, int y);

/* Utility functions */
void initialize_game_map(t_game_map *game_map);
void cleanup_game_map(t_game_map *game_map);
char *trim_line_spaces(char *str);
int convert_rgb_string(char *rgb_str, t_rgb_color *color);
int check_all_configs_set(t_game_map *game_map);
void display_parse_error(char *message);

/* Main parsing */
int		parsing(int ac, char *av[], t_game_map *game_map);
int		check_map(char *file);

/* MLX functions */
void	init_mlx(t_mlx *mlx, t_game_map *game_map);
void	init_player(t_mlx *mlx, t_game_map *game_map);
void	load_textures(t_mlx *mlx);

/* Rendering functions */
int		render_frame(t_mlx *mlx);
void	cast_rays(t_mlx *mlx);
void	draw_vertical_line(t_mlx *mlx, int x, t_ray *ray);
void	put_pixel_to_image(t_mlx *mlx, int x, int y, int color);
unsigned int	get_texture_color(t_mlx *mlx, int tex_num, int tex_x, int tex_y);

/* Movement functions */
void	move_player_forward(t_mlx *mlx);
void	move_player_backward(t_mlx *mlx);
void	move_player_left(t_mlx *mlx);
void	move_player_right(t_mlx *mlx);
void	rotate_player_left(t_mlx *mlx);
void	rotate_player_right(t_mlx *mlx);

/* Hook functions */
int		close_window(t_mlx *mlx);
int		key_press(int keycode, t_mlx *mlx);

/* Utils */
int		is_wall(t_mlx *mlx, double x, double y);

#endif


