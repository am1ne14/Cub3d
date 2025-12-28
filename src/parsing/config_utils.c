/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:58:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_split_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

int	validate_texture_parts(char **parts)
{
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		display_parse_error("Invalid texture format - should be: "\
			"[NO|SO|WE|EA] <path>");
		if (parts)
			free_split_parts(parts);
		return (0);
	}
	return (1);
}

int	validate_color_parts(char **parts)
{
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		display_parse_error("Invalid color format - should be: [F|C] R,G,B");
		if (parts)
			free_split_parts(parts);
		return (0);
	}
	return (1);
}

int	is_texture_identifier(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

int	is_color_identifier(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}
