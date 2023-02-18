# include "../../includes/render.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x *(data->bits_per_px / 8));
	*(unsigned int *)dest = color;
}
