#ifndef STRUCT_H
# define STRUCT_H

# include "stdlib.h"

enum e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_texture{
	size_t	**img_tab[4];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	char	**map;
	double	x;
	double	y;
	char	orientation;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	posX;
	double	posY;
}	t_texture;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_px;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	t_texture	*config;
	void		*init;
	void		*win;
	t_data		img;
	int			img_width;
	int			img_height;
}	t_mlx;

typedef struct s_raycast
{
	double	rayDirX;
	double	rayDirY;
	int		start;
	int		end;
}	t_raycast;

typedef struct s_dda
{
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		side;
}	t_dda;


#endif
