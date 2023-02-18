#ifndef STRUCT_H
# define STRUCT_H

enum e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};
typedef struct s_texture{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	char	**map;
}	t_texture;

typedef struct s_mlx
{
	t_texture	*config;
	void		*init;
	void		*win;
	void		*img;
	char		*img_addr;
	int			img_width;
	int			img_height;
	int			bits_per_px;
	int			line_len;
	int			endian;
	double		x;
	double		y;
	int			orientation;
}	t_mlx;

typedef struct s_raycast
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
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
}	t_dda;


#endif
