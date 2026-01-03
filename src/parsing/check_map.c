/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:21:53 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:49:43 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_map(char *file)
{
	t_game_map	game_map;

	initialize_game_map(&game_map);
	if (!process_config_file(file, &game_map))
	{
		cleanup_game_map(&game_map);
		return (0);
	}
	if (!validate_game_map(&game_map))
	{
		cleanup_game_map(&game_map);
		return (0);
	}
	cleanup_game_map(&game_map);
	return (1);
}
