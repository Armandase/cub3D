#include "../../includes/render.h"

void	texture_to_tab(t_texture *config, t_mlx *mlx)
{
	t_data	*img;
	int		img_len;

	img_len = 64;
	img->img = mlx_xpm_file_to_image(mlx, config->no, &img_len, &img_len);
	img->addr = mlx_get_data_addr (img->img, &(img->bits_per_px),
			&(img->line_len), &(img->endian));
	//convert char ** to tab ** and rev x and y axe
}
