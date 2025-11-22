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
