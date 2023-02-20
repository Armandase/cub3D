#include "../../includes/render.h"

void	swap_axes(size_t ***array)
{
	int	i;
	int	x;
	int	y;
	size_t	tmp;

	x = 0;
	while (x < 64)
	{
		y = 0;	
		while (y < x)
		{
			tmp = (*array)[x][y];
			(*array)[x][y] = (*array)[y][x];
			(*array)[y][x] = tmp;
			y++;
		}
		x++;
	}
}

void	copy_texture_from_img_to_array(t_texture *config, t_mlx *mlx, t_data *img, int i)
{
	int		x;
	int		y;

	x = 0;
	config->img_tab[i] = malloc(sizeof(size_t *) * 64);
	while (x < 64)
	{
		y = 0;
		config->img_tab[i][x] = malloc(sizeof(size_t) * 64);
		while (y < 64)
		{
			config->img_tab[i][x][y] = get_color_from_img(img, x, y);
			y = y + 1;
		}
		x = x + 1;
	}
	swap_axes(&config->img_tab[i]);
}

void	texture_to_tab(t_texture *config, t_mlx *mlx)
{
	int		i;
	int		img_len;
	t_data	*img;

	i = 0;
	img_len = 64;
	while (i < 4)
	{
		if (i == 0)
			img->img = mlx_xpm_file_to_image
				(mlx, config->no, &img_len, &img_len);
		else if (i == 1)
			img->img = mlx_xpm_file_to_image
				(mlx, config->so, &img_len, &img_len);
		else if (i == 2)
			img->img = mlx_xpm_file_to_image
				(mlx, config->ea, &img_len, &img_len);
		else if (i == 3)
			img->img = mlx_xpm_file_to_image
				(mlx, config->we, &img_len, &img_len);
		img->addr = mlx_get_data_addr (img->img, &(img->bits_per_px),
				&(img->line_len), &(img->endian));
		copy_texture_from_img_to_array(config, mlx, img, i);
		i++;
	}
}
