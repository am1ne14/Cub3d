#include "cub3d.h"

//paths of textures
//
//rgb flour ceiling 
//
// map


int	check_map_file(char *str)
{
	int fd;
	fd = open(str, O_RDONLY);
	if(fd < 0)
		exit((perror("Error : can't open map file"), 1));
}
bool	parsefile(char *str)
{
	//cheks the file 
	//parse the textures
	// pars the rgb collors
	// pars the map
	int fd;
	fd = check_map_file(str))
	if (fd < 0)
		return false;
	if (!parse_texture_part(str))
		return false;
	if (parse_rgb_part(str))
}

int main(int arc, char **arv)
{
	if (arc == 2)
	{
		parsefile(arv[1]);
		rendreing_the_game(arv);
	}
	
	return 0;
}
