/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:37:27 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_arguments(int ac, char **av)
{
	char	*extension;

	if (ac != 2)
	{
		display_parse_error("Invalid number of arguments");
		return (0);
	}
	if (ft_strlen(av[1]) < 5)
	{
		display_parse_error("Invalid file name");
		return (0);
	}
	extension = av[1] + ft_strlen(av[1]) - 4;
	if (ft_strncmp(extension, ".cub", 4) != 0)
	{
		display_parse_error("File must have .cub extension");
		return (0);
	}
	return (1);
}

int	parsing(int ac, char *av[], t_game_map *game_map)
{
	if (!validate_arguments(ac, av))
		return (0);
	initialize_game_map(game_map);
	if (!process_config_file(av[1], game_map))
	{
		reset_gnl_stash();
		cleanup_game_map(game_map);
		return (0);
	}
	if (!validate_game_map(game_map))
	{
		reset_gnl_stash();
		cleanup_game_map(game_map);
		return (0);
	}
	return (1);
}
