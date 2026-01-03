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

static int	is_map_line(char *line)
{
	int		map_char_found;
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	map_char_found = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (!check_valid_map_character(line[i]))
			return (0);
		map_char_found = 1;
		i++;
	}
	return (map_char_found);
}

static int	dispatch_config(char *trimmed_line, int map_hint,
			t_game_map *game_map)
{
	if (is_texture_identifier(trimmed_line))
		return (handle_texture_config(trimmed_line, game_map));
	if (is_color_identifier(trimmed_line))
		return (handle_color_config(trimmed_line, game_map));
	if (map_hint || check_all_configs_set(game_map))
		return (2);
	display_parse_error("Invalid configuration line");
	return (0);
}

int	process_config_line(char *line, t_game_map *game_map)
{
	char	*trimmed_line;
	int		map_hint;
	int		result;

	map_hint = is_map_line(line);
	trimmed_line = trim_line_spaces(line);
	if (!trimmed_line)
		return (display_parse_error("Memory allocation failed"), 0);
	if (ft_strlen(trimmed_line) == 0)
		return (free(trimmed_line), 1);
	result = dispatch_config(trimmed_line, map_hint, game_map);
	free(trimmed_line);
	return (result);
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
			return (0);
		}
		if (parse_result == 2)
		{
			if (!handle_map_start(line, game_map, fd))
				return (0);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (-1);
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
	close(fd);
	if (result == 1)
		return (1);
	if (result == -1)
		display_parse_error("No map found in file");
	return (0);
}
