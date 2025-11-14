#include "../../includes/cub3d.h"

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		close_window(mlx);
	else if (keycode == 119)
		move_player_forward(mlx);
	else if (keycode == 115)
		move_player_backward(mlx);
	else if (keycode == 97)
		move_player_left(mlx);
	else if (keycode == 100)
		move_player_right(mlx);
	else if (keycode == 65361)
		rotate_player_left(mlx);
	else if (keycode == 65363)
		rotate_player_right(mlx);
	return (0);
}

