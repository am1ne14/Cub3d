/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:38:12 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/28 21:43:01 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		mlx->key_w = 1;
	else if (keycode == 115)
		mlx->key_s = 1;
	else if (keycode == 97)
		mlx->key_a = 1;
	else if (keycode == 100)
		mlx->key_d = 1;
	else if (keycode == 65363)
		mlx->key_left = 1;
	else if (keycode == 65361)
		mlx->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == 119)
		mlx->key_w = 0;
	else if (keycode == 115)
		mlx->key_s = 0;
	else if (keycode == 97)
		mlx->key_a = 0;
	else if (keycode == 100)
		mlx->key_d = 0;
	else if (keycode == 65363)
		mlx->key_left = 0;
	else if (keycode == 65361)
		mlx->key_right = 0;
	return (0);
}
