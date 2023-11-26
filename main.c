#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <pthread.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "parse.h"
#include "vec3d.h"
#include "init.h"
#include "colors.h"
#include "camera.h"
#include "ray.h"
#include "hit.h"
#include "render.h"

/**
 * @brief Main entry point for rendering the scene.
 * 
 * @param arg Argument structure containing the scene and the image struct.
 * @return void* 
 */
static void	*do_render(void *arg)
{
	t_render	*render;
	t_scene		*scene;
	mlx_image_t	*image;
	int			j_off;
	int			ij[2];

	render = (t_render *)arg;
	scene = render->scene;
	image = render->image;
	j_off = ((int)image->height / THREAD_NO) * render->i;
	ij[1] = 0;
	while (ij[1] < (int)image->height / THREAD_NO)
	{
		ij[0] = 0;
		while (ij[0] < (int)image->width)
		{
			mlx_put_pixel(image, ij[0], ij[1] + j_off, get_rgba_from_tcol(
					get_px_color(scene, ij[0], ij[1] + j_off)));
			++(ij[0]);
		}
		++(ij[1]);
	}
	return (NULL);
}

/**
 * @brief Util function for establishing the ESC hook for closing the window.
 * 
 * @param in Pointer to the mlx and scene parameter.
 */
static void	escape_hook(void *in)
{
	t_param		*param;

	param = (t_param *)in;
	if (mlx_is_key_down(param->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(param->mlx);
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_param			p;
	t_scene			s;
	mlx_image_t		*image;
	t_render		r[THREAD_NO];
	int				i;

	if (argc != 2)
		return (EXIT_FAILURE);
	i = 0;
	p = (t_param){};
	if (!parse(&s, (char *)argv[1]) || !init_main(&p.mlx, &image, &s.cam))
		return (EXIT_FAILURE);
	p.scene = &s;
	p.image = image;
	while (i < THREAD_NO)
	{
		r[i] = (t_render){.i = i, .image = image, .scene = &s};
		if (pthread_create(&p.thread[i], NULL, &do_render, r + i))
			return (EXIT_FAILURE);
		++i;
	}
	mlx_loop_hook(p.mlx, escape_hook, &p);
	mlx_loop(p.mlx);
	mlx_terminate(p.mlx);
	return (free(s.lights), free(s.objs), EXIT_SUCCESS);
}
