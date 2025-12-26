/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:37:27 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/19 23:37:31 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parsing(int ac, char *av[], t_game_map *game_map)
{
	if (!validate_arguments(ac, av))
		return (0);
	initialize_game_map(game_map);
	if (!process_config_file(av[1], game_map))
	{
		cleanup_game_map(game_map);
		return (0);
	}
	if (!validate_game_map(game_map))
	{
		cleanup_game_map(game_map);
		return (0);
	}
	return (1);
}
