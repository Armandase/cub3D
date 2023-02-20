# include "../../includes/render.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		dest = data->addr + (y * data->line_len + x *(data->bits_per_px / 8));
		*(unsigned int *)dest = color;
	}
}

size_t	get_color_from_img(t_data *data, int x, int y)
{
	int		offset;
	size_t	ret;
	int		r;
	int		g;
	int		b;

	offset = (y * data->line_len + x * (data->bits_per_px / 8));
	r = data->addr[offset + 2];
	g = data->addr[offset + 1];
	b = data->addr[offset];
	ret = (r << 16) + (g << 8) + b;
	return (ret);
}
