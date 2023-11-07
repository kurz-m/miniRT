#include "libft.h"
#include "structs.h"
#include "parse.h"
#include "miniRT.h"
#include "vec3d.h"
#include "init.h"
#include "colors.h"
#include "ray.h"
#include "hit.h"
#include <pthread.h>

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
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


t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	double		t;
	t_vec3d		norm;
	t_sphere	*sp;
	t_color		new;

	t = hit_sphere(scene, ray);
	sp = (t_sphere *)scene->objects->content;
	if (t > 0.0)
	{
		norm = vec_norm(vec_sub(ray_at(ray, t), sp->pos));
		new = color_new(norm.x * 255, norm.y * 255, norm.z * 255);
		new = color_add(new, color_new(255, 255, 255));
		return (color_scale(new, 0.5));
	}

	t_vec3d unit_direction = vec_norm(ray->direction);
	double a = 0.5 * (unit_direction.y + 1.0);
	t_color start_col = color_scale(color_new(255, 255, 255), (1.0 - a));
	t_color end_col = color_scale(color_new(0, 0, 255), a);
	return color_add(start_col, end_col);
}

typedef struct s_render
{
	t_scene		*scene;
	mlx_image_t	*image;
}	t_render;

void	*do_render(void *arg)
{
	t_render	*render;
	t_scene 	*scene;
	mlx_image_t	*image;
	t_point3d	pixel_center;
	t_vec3d		ray_dir;
	t_ray		ray;
	t_color		color;

	render = (t_render *)arg;
	scene = render->scene;
	image = render->image;
	for (int j = 0; j < (int)image->height; ++j) {
		for (int i = 0; i < (int)image->width; ++i) {
			pixel_center = get_pixel_center(&scene->cam, i, j);
			ray_dir = vec_sub(pixel_center, scene->cam.pov);
			ray = ray_new(scene->cam.pov, ray_dir);
			color = get_ray_color(scene, &ray);
			mlx_put_pixel(image, i, j, get_rgba_from_tcol(color));
		}
	}
	return (NULL);
}

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;
	t_scene	scene;
	pthread_t	thread;
	t_render	render;

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
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	render = (t_render){.image = image, .scene = &scene};
	pthread_create(&thread, NULL, &do_render, &render);

	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

