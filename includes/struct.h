#ifndef STRUCT_H
# define STRUCT_H

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
}	t_mlx;

#endif
