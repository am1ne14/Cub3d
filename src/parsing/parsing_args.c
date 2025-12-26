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
