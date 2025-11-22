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

static int	is_texture_identifier(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

static int	is_color_identifier(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

static int	handle_texture_line(char *trimmed_line, t_game_map *game_map)
{
	if (!handle_texture_config(trimmed_line, game_map))
	{
		free(trimmed_line);
		return (0);
	}
	return (1);
}

static int	handle_color_line(char *trimmed_line, t_game_map *game_map)
{
	if (!handle_color_config(trimmed_line, game_map))
	{
		free(trimmed_line);
		return (0);
	}
	return (1);
}

static int	process_config_line(char *line, t_game_map *game_map)
{
	char	*trimmed_line;

	trimmed_line = trim_line_spaces(line);
	if (!trimmed_line || ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		return (1);
	}
	if (is_texture_identifier(trimmed_line))
	{
		if (!handle_texture_line(trimmed_line, game_map))
			return (0);
	}
	else if (is_color_identifier(trimmed_line))
	{
		if (!handle_color_line(trimmed_line, game_map))
			return (0);
	}
	else if (check_valid_map_character(trimmed_line[0]))
	{
		free(trimmed_line);
		return (2);
	}
	free(trimmed_line);
	return (1);
}

static int	init_map_grid(t_game_map *game_map, char *trimmed, int fd)
{
	game_map->map_grid = malloc(sizeof(char *) * 10);
	if (!game_map->map_grid)
	{
		free(trimmed);
		close(fd);
		return (0);
	}
	if (!validate_map_line(trimmed, game_map, 0))
	{
		free(trimmed);
		close(fd);
		return (0);
	}
	game_map->map_grid[0] = trimmed;
	game_map->map_height = 1;
	game_map->map_width = ft_strlen(trimmed);
	return (1);
}

static int	process_first_map_line(char *trimmed, t_game_map *game_map, int fd)
{
	if (trimmed && ft_strlen(trimmed) > 0)
	{
		if (!init_map_grid(game_map, trimmed, fd))
			return (0);
	}
	else
	{
		if (trimmed)
			free(trimmed);
	}
	return (1);
}

static int	handle_map_start(char *line, t_game_map *game_map, int fd)
{
	char	*trimmed;

	if (!check_all_configs_set(game_map))
	{
		display_parse_error("Missing config parameters");
		free(line);
		close(fd);
		return (0);
	}
	trimmed = trim_line_spaces(line);
	free(line);
	if (!process_first_map_line(trimmed, game_map, fd))
		return (0);
	if (!process_map_data(fd, game_map))
	{
		close(fd);
		return (0);
	}
	return (1);
}

static int	process_file_lines(int fd, t_game_map *game_map)
{
	char	*line;
	int		parse_result;

	while ((line = get_next_line(fd)) != NULL)
	{
		parse_result = process_config_line(line, game_map);
		if (parse_result == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		if (parse_result == 2)
		{
			if (!handle_map_start(line, game_map, fd))
				return (0);
			return (1);
		}
		free(line);
	}
	return (0);
}

int	process_config_file(char *filename, t_game_map *game_map)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		display_parse_error("Cannot open file");
		return (0);
	}
	if (!process_file_lines(fd, game_map))
	{
		display_parse_error("No map found in file");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

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
