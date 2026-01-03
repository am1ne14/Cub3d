/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_textures_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:23:00 by bamdjar           #+#    #+#             */
/*   Updated: 2026/01/03 13:40:30 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_texture_id(char *line, char **id, int *idx)
{
	*idx = 0;
	while (line[*idx] && line[*idx] != ' ' && line[*idx] != '\t')
		(*idx)++;
	if (*idx == 0 || !line[*idx])
		return (display_parse_error("Invalid texture format - should be: "
				"[NO|SO|WE|EA] <path>"), 0);
	*id = ft_substr(line, 0, *idx);
	if (!*id)
		return (0);
	while (line[*idx] == ' ' || line[*idx] == '\t')
		(*idx)++;
	return (1);
}

static int	parse_texture_path(char *line, int idx, char **path)
{
	*path = trim_line_spaces(line + idx);
	if (!*path || ft_strlen(*path) == 0)
	{
		if (*path)
			free(*path);
		return (display_parse_error("Invalid texture format - should be: "
				"[NO|SO|WE|EA] <path>"), 0);
	}
	return (1);
}

int	handle_texture_config(char *line, t_game_map *game_map)
{
	char	*id;
	char	*path;
	int		idx;

	if (!parse_texture_id(line, &id, &idx))
		return (0);
	if (!parse_texture_path(line, idx, &path))
		return (free(id), 0);
	if (!store_texture_path(id, path, game_map))
	{
		free(id);
		free(path);
		return (0);
	}
	free(id);
	free(path);
	return (1);
}
