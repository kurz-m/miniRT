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
#include <time.h>

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "MLX42.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------



// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// }

// -----------------------------------------------------------------------------

// ambient color model: the ambient color vector is used as a scale for the 
// obj color. 
// see here https://learnwebgl.brown37.net/09_lights/lights_ambient.html
t_color	get_ambient_color(t_scene *sc, t_hitrec *hit)
{
	double	hr;
	double	hg;
	double	hb;

	hr = sc->amb.color.r * sc->amb.ratio / 255;
	hg = sc->amb.color.g * sc->amb.ratio / 255;
	hb = sc->amb.color.b * sc->amb.ratio / 255;
	return ((t_color){
		.r = hit->obj->u.color.r * hr,
		.g = hit->obj->u.color.g * hg,
		.b = hit->obj->u.color.b * hb
	});
}

t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_color		new;
	t_hitrec	hitrec;
	t_vec3d		norm;

	if (hit_objects(scene, ray, &hitrec))
	{
		// return (get_ambient_color(scene, &hitrec));
		norm = hitrec.normal;
		new = color_new(norm.x * 255, norm.y * 255, norm.z * 255);
		new = color_add(new, color_new(255, 255, 255));
		return (color_scale(new, 0.5));
	}
	t_vec3d unit_direction = vec_norm(ray->dir);
	double a = 0.5 * (unit_direction.y + 1.0);
	t_color start_col = color_scale(color_new(255, 255, 255), (1.0 - a));
	t_color end_col = color_scale(color_new(0, 0, 255), a);
	return color_add(start_col, end_col);
	// return (color_new(0,0,0));
}

typedef struct s_render
{
	t_scene		*scene;
	mlx_image_t	*image;
}	t_render;

typedef struct s_param
{
	mlx_t		*mlx;
	pthread_t	thread;
	t_render	render;
}	t_param;

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
			for (int samples = 0; samples < AA_SAMPLES - 1; samples++) {
				pixel_center = get_pixel_random(&scene->cam, i, j);
				ray_dir = vec_sub(pixel_center, scene->cam.pov);
				ray = ray_new(scene->cam.pov, ray_dir);
				color = color_scale(color_add(get_ray_color(scene, &ray), color), 0.5);
			}
			mlx_put_pixel(image, i, j, get_rgba_from_tcol(color));
		}
	}
	return (NULL);
}

// static void	move_cam(t_scene *sc, t_vec3d mov)
// {
// 	sc->cam.pov = vec_add(sc->cam.pov, mov);
// }

// static void	turn_cam(t_scene *sc, double horizontal, double vertical)
// {
// 	t_vec3d	new;

// 	if (horizontal)
// 		new = (t_vec3d){.x = horizontal};
// 	else if(vertical)
// 		new = (t_vec3d){.y = vertical};
// 	sc->cam.dir = vec_norm(vec_add(sc->cam.dir, new));
// }

void	ft_turn_hook(void *in)
{
	t_param		*param;
	static bool	changed;

	param = (t_param *)in;
	if (mlx_is_key_down(param->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(param->mlx);
	// if (mlx_is_key_down(param->mlx, MLX_KEY_D))
	// 	move_cam(param->render.scene, vec_new(2,0,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_A))
	// 	move_cam(param->render.scene, vec_new(-2,0,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_W))
	// 	move_cam(param->render.scene, vec_new(0,2,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_S))
	// 	move_cam(param->render.scene, vec_new(0,-2,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_UP))
	// 	turn_cam(param->render.scene, 0, 0.2), init_cam(&(param->render.scene->cam)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_DOWN))
	// 	turn_cam(param->render.scene, 0, -0.2), init_cam(&(param->render.scene->cam)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_LEFT))
	// 	turn_cam(param->render.scene, -0.2, 0), init_cam(&(param->render.scene->cam)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_RIGHT))
	// 	turn_cam(param->render.scene, 0.2, 0), init_cam(&(param->render.scene->cam)), changed = true;
	// if (changed)
	// {
	// 	if (param->thread)
	// 	{
	// 		// pthread_kill(param->thread, SIGINT);
	// 		pthread_cancel(param->thread);
	// 		pthread_join(param->thread, NULL);
	// 	}
	// 	pthread_create(&param->thread, NULL, &do_render, &(param->render));
	// 	changed = false;
	// }
}

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;
	t_scene	scene;
	t_param		param;

	scene = (t_scene){};
	parse(&scene, "test.rt");
	init_cam(&scene.cam);
	srand(time(NULL));

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

	param = (t_param)
	{
		.mlx = mlx,
		.render = (t_render){.image = image, .scene = &scene},
	};
	pthread_create(&param.thread, NULL, &do_render, &(param.render));
	// mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop_hook(mlx, ft_turn_hook, &param);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

