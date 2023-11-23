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

void	*do_render(void *arg)
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

void	escape_hook(void *in)
{
	t_param		*param;

	param = (t_param *)in;
	if (mlx_is_key_down(param->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(param->mlx);
}

#include <stdio.h>

void cleanup() {
	char command[100];
	pid_t pid = getpid();
	sprintf(command, "leaks %d", pid);
	system(command);
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_param			param;
	t_scene			scene;
	mlx_image_t		*image;
	t_render		r[THREAD_NO];
	int				i;

	atexit(cleanup);
	if (argc != 2)
		return (EXIT_FAILURE);
	i = 0;
	if (parse(&scene, (char *)argv[1]) == false)
		return (EXIT_FAILURE);
	init_cam(&scene.cam);
	param = (t_param){.image = image, .scene = &scene};
	if (init_mlx(&param.mlx, &image))
		return (EXIT_FAILURE);
	while (i < THREAD_NO)
	{
		r[i] = (t_render){.i = i, .image = image, .scene = &scene};
		if (pthread_create(&param.thread[i], NULL, &do_render, r + i))
			return (EXIT_FAILURE);
		++i;
	}
	mlx_loop_hook(param.mlx, escape_hook, &param);
	mlx_loop(param.mlx);
	free(scene.lights);
	free(scene.objs);
	mlx_terminate(param.mlx);
	return (EXIT_SUCCESS);
}
