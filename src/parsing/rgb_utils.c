/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:58:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/12/28 21:50:25 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_rgb_parts(char **rgb_parts)
{
	int	i;

	i = 0;
	while (rgb_parts[i] && i < 3)
		i++;
	return (i);
}

void	free_rgb_parts(char **rgb_parts)
{
	int	i;

	i = 0;
	while (rgb_parts[i])
		free(rgb_parts[i++]);
	free(rgb_parts);
}

static int	is_valid_number(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		has_digit = 1;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (has_digit && str[i] == '\0');
}

int	validate_rgb_values(char **rgb_parts, int *values)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(rgb_parts[i]))
		{
			free_rgb_parts(rgb_parts);
			display_parse_error("RGB values must be valid numbers");
			return (0);
		}
		values[i] = ft_atoi(rgb_parts[i]);
		if (values[i] < 0 || values[i] > 255)
		{
			free_rgb_parts(rgb_parts);
			display_parse_error("RGB values must be between 0 and 255");
			return (0);
		}
		i++;
	}
	return (1);
}

int	convert_rgb_string(char *rgb_str, t_rgb_color *color)
{
	char	**rgb_parts;
	int		values[3];
	int		part_count;

	rgb_parts = ft_split(rgb_str, ',');
	if (!rgb_parts)
		return (0);
	part_count = count_rgb_parts(rgb_parts);
	if (part_count != 3 || rgb_parts[3])
	{
		free_rgb_parts(rgb_parts);
		display_parse_error("RGB color must have exactly 3 values");
		return (0);
	}
	if (!validate_rgb_values(rgb_parts, values))
		return (0);
	color->red = values[0];
	color->green = values[1];
	color->blue = values[2];
	free_rgb_parts(rgb_parts);
	return (1);
}
