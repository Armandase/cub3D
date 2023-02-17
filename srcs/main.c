#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/render.h"

int	main(int ac, char **av)
{
	t_texture	config;

	config = init_texture();
	parsing(ac, av, &config);
	render(&config);
	return (0);
}
