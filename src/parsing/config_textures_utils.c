#include "../../includes/cub3d.h"

int	handle_texture_config(char *line, t_game_map *game_map)
{
	char	**parts;
	int		result;

	parts = ft_split(line, ' ');
	if (!validate_texture_parts(parts))
		return (0);
	result = store_texture_path(parts[0], parts[1], game_map);
	free_split_parts(parts);
	return (result);
}
