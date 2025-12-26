/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:37:45 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/26 14:37:49 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(t_mlx *mlx)
{
	if (mlx->key_w)
		move_player_forward(mlx);
	if (mlx->key_s)
		move_player_backward(mlx);
	if (mlx->key_a)
		move_player_left(mlx);
	if (mlx->key_d)
		move_player_right(mlx);
	if (mlx->key_left)
		rotate_player_left(mlx);
	if (mlx->key_right)
		rotate_player_right(mlx);
	render_frame(mlx);
	return (0);
}
