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
#include <math.h>
#include <fcntl.h>
#include "MLX42.h"


// ambient color model: the ambient color vector is used as a scale for the 
// obj color. 
// see here https://learnwebgl.brown37.net/09_lights/lights_ambient.html
t_color	get_ambient_color(t_scene *sc, t_hitrec *hit)
{
	return ((t_color){
		.r = hit->obj->color.r * sc->amb.color.r * sc->amb.ratio,
		.g = hit->obj->color.g * sc->amb.color.g * sc->amb.ratio,
		.b = hit->obj->color.b * sc->amb.color.b * sc->amb.ratio,
	});
}

t_color	get_diffuse_light(t_color *obj_color, double angle, t_obj *obj)
{
	return ((t_color){
		.r = obj_color->r * angle * obj->light.brightness * obj->color.r,
		.g = obj_color->g * angle * obj->light.brightness * obj->color.g,
		.b = obj_color->b * angle * obj->light.brightness * obj->color.b,
	});
}

void	color_clamp(t_color *color)
{
	if (color->r > 1.0)
		color->r = 1.0;
	if (color->g > 1.0)
		color->g = 1.0;
	if (color->b > 1.0)
		color->b = 1.0;
}

t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_hitrec	hitrec;
	t_hitrec	hit_light;
	t_vec3d		norm;
	t_color		color;
	t_ray		light_ray;
	double		angle;
	int			i;

	color = color_new(0, 0, 0);
	if (hit_objects(scene, ray, &hitrec))
	{
		color = color_add(color, get_ambient_color(scene, &hitrec));
		i = 0;
		while (i < scene->n_light)
		{
			light_ray = ray_new(hitrec.p, vec_sub(scene->lights[i].pos, hitrec.p));
			norm = hitrec.normal;
			hit_objects(scene, &light_ray, &hit_light);
			if (hit_light.t >= 0 && hit_light.t >= vec_len(vec_sub(scene->lights[i].pos, hitrec.p)))
			{
				angle = fmax(vec_dot(norm, light_ray.dir), 0.0f);
				color = color_add(color, get_diffuse_light(&(hitrec.obj->color), angle, scene->lights + i));
				color_clamp(&color);
			}
			i++;
		}
		return (color);
	}
	t_vec3d unit_direction = vec_norm(ray->dir);
	double a = 0.5 * (unit_direction.y + 1.0);
	t_color start_col = color_scale(color_new(1, 1, 1), (1.0 - a));
	t_color end_col = color_scale(color_new(0, 0, 1), a);
	return color_add(start_col, end_col);
	// return (color_new(0,0,0));
}

typedef struct s_render
{
	t_scene		*scene;
	mlx_image_t	*image;
	int			i;
}	t_render;

typedef struct s_param
{
	mlx_t		*mlx;
	pthread_t	thread[THREAD_NO];
	t_scene		*scene;
	mlx_image_t	*image;
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
	int			th_off;
	// int			fd;

	// fd = open("img.ppm", O_WRONLY | O_CREAT);
	render = (t_render *)arg;
	scene = render->scene;
	image = render->image;
	// ft_fprintf(fd, "P3\n");
	// ft_fprintf(fd, "%d %d\n255\n", WIDTH, HEIGHT);
	th_off = ((int)image->height / THREAD_NO) * render->i;
	for (int j = 0; j < (int)image->height / THREAD_NO; ++j) {
		for (int i = 0; i < (int)image->width; ++i) {
			pixel_center = get_pixel_center(&scene->cam, i, j + th_off);
			ray_dir = vec_sub(pixel_center, scene->cam.pov);
			ray = ray_new(scene->cam.pov, ray_dir);
			color = get_ray_color(scene, &ray);
			// for (int samples = 0; samples < AA_SAMPLES - 1; samples++) {
			// 	pixel_center = get_pixel_random(&scene->cam, i, j);
			// 	ray_dir = vec_sub(pixel_center, scene->cam.pov);
			// 	ray = ray_new(scene->cam.pov, ray_dir);
			// 	color = color_scale(color_add(get_ray_color(scene, &ray), color), 0.5);
			// }
			// ft_fprintf(fd, "%i %i %i\n", color.r, color.g, color.b);
			mlx_put_pixel(image, i, j + th_off, get_rgba_from_tcol(color));
		}
	}
	// close(fd);
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
	//static bool	changed;

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
	mlx_t*			mlx;
	t_scene			scene;
	t_param			param;
	mlx_image_t*	image;
	t_render		r[THREAD_NO];
	int				i;

	if (argc != 2)
		return (EXIT_FAILURE);
	scene = (t_scene){};
	i = 0;
	parse(&scene, (char *)argv[1]);
	init_cam(&scene.cam);
	if (init_mlx(&mlx, &image))
		return (EXIT_FAILURE);
	param = (t_param){.mlx = mlx, .image = image, .scene = &scene};
	while (i < THREAD_NO)
	{
		r[i] = (t_render){
			.i = i,
			.image = image,
			.scene = &scene,
		};
		if (pthread_create(&param.thread[i], NULL, &do_render, r + i))
			return (EXIT_FAILURE);
		++i;
	}
	mlx_loop_hook(mlx, ft_turn_hook, &param);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

