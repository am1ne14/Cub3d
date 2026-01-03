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
	(void)parts;
	return (1);
}

int	validate_color_parts(char **parts)
{
	(void)parts;
	return (1);
}

int	is_texture_identifier(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (0);
	return ((line[0] == 'N' && line[1] == 'O'
			&& (line[2] == ' ' || line[2] == '\t'))
		|| (line[0] == 'S' && line[1] == 'O'
			&& (line[2] == ' ' || line[2] == '\t'))
		|| (line[0] == 'W' && line[1] == 'E'
			&& (line[2] == ' ' || line[2] == '\t'))
		|| (line[0] == 'E' && line[1] == 'A'
			&& (line[2] == ' ' || line[2] == '\t')));
}

int	is_color_identifier(char *line)
{
	if (!line || ft_strlen(line) < 2)
		return (0);
	return ((line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		|| (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t')));
}
