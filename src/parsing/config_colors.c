/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:57:29 by bamdjar           #+#    #+#             */
/*   Updated: 2026/01/03 13:39:59 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	store_color_config(char *identifier, t_rgb_color *color,
	char *rgb_str, t_game_map *game_map)
{
	if (color->red >= 0)
	{
		if (ft_strncmp(identifier, "F", 1) == 0)
			display_parse_error("Duplicate Floor color");
		else
			display_parse_error("Duplicate Ceiling color");
		return (0);
	}
	if (!convert_rgb_string(rgb_str, color))
		return (0);
	game_map->config_count++;
	return (1);
}

static int	parse_color_id(char *line, char **id, int *idx)
{
	*idx = 0;
	while (line[*idx] && line[*idx] != ' ' && line[*idx] != '\t')
		(*idx)++;
	if (*idx != 1 || !line[*idx])
		return (display_parse_error("Invalid color format - should be: "
				"[F|C] R,G,B"), 0);
	*id = ft_substr(line, 0, *idx);
	if (!*id)
		return (0);
	while (line[*idx] == ' ' || line[*idx] == '\t')
		(*idx)++;
	return (1);
}

static int	parse_color_rgb(char *line, int idx, char **rgb)
{
	*rgb = trim_line_spaces(line + idx);
	if (!*rgb || ft_strlen(*rgb) == 0)
	{
		if (*rgb)
			free(*rgb);
		return (display_parse_error("Invalid color format - should be: "
				"[F|C] R,G,B"), 0);
	}
	return (1);
}

int	handle_color_config(char *line, t_game_map *game_map)
{
	char	*id;
	char	*rgb;
	int		i;

	if (!parse_color_id(line, &id, &i))
		return (0);
	if (!parse_color_rgb(line, i, &rgb))
		return (free(id), 0);
	if (id[0] == 'F')
		i = store_color_config(id, &game_map->floor_rgb, rgb, game_map);
	else if (id[0] == 'C')
		i = store_color_config(id, &game_map->ceiling_rgb, rgb, game_map);
	else
	{
		display_parse_error("Invalid color identifier - must be F or C");
		i = 0;
	}
	free(id);
	free(rgb);
	return (i);
}
