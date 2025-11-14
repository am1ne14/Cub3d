/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 02:30:33 by mtaybi            #+#    #+#             */
/*   Updated: 2025/09/09 02:36:23 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char *av[])
{
    t_mlx *mlx = malloc(sizeof(t_mlx));
    t_game_map *game_map = malloc(sizeof(t_game_map));
    
    if (!parsing(ac, av, game_map))
    {
        free(mlx);
        free(game_map);
        return 1;
    }
    
    init_mlx(mlx, game_map);

    mlx_loop(mlx->mlx_ptr);
    return 0;
}