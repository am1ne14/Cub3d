#include "../includes/cub3d.h"



int main(int arc, char **arv)
{
    t_mlx mlx;
    t_game_map game_map;

    if (!parsing(arc, arv, &game_map))
        return 1;

    init_mlx(&mlx, &game_map);

    mlx_loop(mlx.mlx_ptr);
    return 0;
}
