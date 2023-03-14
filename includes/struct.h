#ifndef STRUCT_H
# define STRUCT_H

# include "stdlib.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

enum e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_texture
{
	uint32_t	**img_tab[4];
	uint32_t	**img_door;
	bool		door;
	bool		door_opened;
	bool		middle;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
	char		**map;
	double		x;
	double		y;
	char		orientation;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
}	t_texture;

typedef struct s_mlx
{
	t_texture	*config;
	mlx_t		*init;
	void		*win;
	mlx_image_t	*img;
	int			img_width;
	int			img_height;
}	t_mlx;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	tex_pos;
	double	step;
	int		tex_x;
	int		start;
	int		end;
}	t_raycast;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		orientation;
	int		wall_height;
}	t_dda;

#endif
