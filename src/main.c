
#include "../includes/cub3d.h"

int main(int ac, char *av[])
{
    t_mlx *mlx = malloc(sizeof(t_mlx));
    t_game_map *game_map = malloc(sizeof(t_game_map));
    
    if (!parsing(ac, av, game_map))
    {
        free(mlx);
        free(game_map);
        return 1;
    }
    
    init_mlx(mlx, game_map);

    mlx_loop(mlx->mlx_ptr);
    return 0;
}
