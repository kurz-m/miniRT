#include "libft.h"
#include "miniRT.h"
#include "colors.h"

// int	main(void)
// {
// 	t_scene	scene;
// 
// 	scene = (t_scene){};
// 	parse(&scene, "test.rt");
// 	return (0);
// }
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	for (int j = 0; j < (int)image->height; ++j) {
		for (int i = 0; i < (int)image->width; ++i) {
			double r = (double)i / (image->width - 1);
			double g = (double)j / (image->height - 1);
			double b = 0;

			int ir = (int)(255.99 * r);
			int ig = (int)(255.99 * g);
			int ib = (int)(255.99 * b);
			uint32_t	color = get_rgba(ir, ig, ib, 255);
			mlx_put_pixel(image, i, j, color);
		}
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	 mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

