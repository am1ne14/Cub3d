#ifndef CUB3D_H
#define

typedef struct s_dir
{
	char	*no;
	char	*so;
	char	*ea:
	char	*we;
}	t_dir;

typedef	struct s_rgb
{
	int	r;
	int	g;
	int 	b;
}	t_rgb;

typedef	struct s_map
{
	t_dir	dir;
	t_rgb	rgb;
	char	*map[];
}	t_map;

#endif
