#include "libft.h"
#include "miniRT.h"
#include "vec3d.h"
#include "init.h"
#include "colors.h"

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42.h"

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
	t_scene	scene;
	t_point3d	pixel_center;
	t_vec3d		ray_dir;

	scene = (t_scene){};
	parse(&scene, "test.rt");
	init_cam(&scene.cam);

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
			pixel_center = 
			double r = (double)i / (image->width - 1);
			double g = (double)j / (image->height - 1);
			double b = 0;

			int ir = (int)(255 * r);
			int ig = (int)(255 * g);
			int ib = (int)(255 * b);
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

