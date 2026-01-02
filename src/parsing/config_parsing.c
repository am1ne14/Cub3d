/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:57:39 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	process_config_line(char *line, t_game_map *game_map)
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

static int	process_file_lines(int fd, t_game_map *game_map)
{
	char	*line;
	int		parse_result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_result = process_config_line(line, game_map);
		if (parse_result == 0)
		{
			free(line);
			close(fd);
			return (-1);
		}
		if (parse_result == 2)
		{
			if (!handle_map_start(line, game_map, fd))
				return (-1);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	process_config_file(char *filename, t_game_map *game_map)
{
	int	fd;
	int	result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		display_parse_error("Cannot open file");
		return (0);
	}
	result = process_file_lines(fd, game_map);
	if (result <= 0)
	{
		if (result == 0)
			display_parse_error("No map found in file");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
