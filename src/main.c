/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:38:31 by mohel-am          #+#    #+#             */
/*   Updated: 2025/12/26 14:38:35 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int arc, char **arv)
{
	t_mlx		mlx;
	t_game_map	game_map;

	if (!parsing(arc, arv, &game_map))
		return (1);
	init_mlx(&mlx, &game_map);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
