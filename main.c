#include <pthread.h>
#include "MLX42.h"
#include "libft.h"
#include "structs.h"
#include "parse.h"
#include "miniRT.h"
#include "vec3d.h"
#include "init.h"
#include "colors.h"
#include "ray.h"
#include "hit.h"
#include <time.h>
#include <math.h>
#include <fcntl.h>

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

static t_color	get_obj_lumination(t_scene *scene, t_hitrec *hitrec)
{
	double		angle;
	int			i;
	t_lumi		l;

	l.color = get_ambient_color(scene, hitrec);
	i = -1;
	while (++i < scene->n_light)
	{
		l.light_ray = ray_new(hitrec->p,
				vec_sub(scene->lights[i].pos, hitrec->p));
		l.norm = hitrec->normal;
		hit_objects(scene, &l.light_ray, &l.hit_light);
		if (l.hit_light.t >= 0 && l.hit_light.t >= vec_len(vec_sub(
					scene->lights[i].pos, hitrec->p)))
		{
			angle = fmax(vec_dot(l.norm, l.light_ray.dir), 0.0f);
			l.color = color_add(l.color, get_diffuse_light(
						&(hitrec->obj->color), angle, scene->lights + i));
			color_clamp(&l.color);
		}
	}
	return (l.color);
}

t_color	get_background_color(t_ray *ray)
{
	t_vec3d	unit_direction;
	double	a;
	t_color	start_col;
	t_color	end_col;

	unit_direction = vec_norm(ray->dir);
	a = 0.5 * (unit_direction.y + 1.0);
	start_col = color_scale(color_new(1, 1, 1), (1.0 - a));
	end_col = color_scale(color_new(0, 0, 1), a);
	return (color_add(start_col, end_col));
}

t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_hitrec	hitrec;
	t_color		color;

	color = color_new(0, 0, 0);
	if (hit_objects(scene, ray, &hitrec))
	{
		return (color_add(color, get_obj_lumination(scene, &hitrec)));
	}
	return (get_background_color(ray));
}

t_color	get_px_color(t_scene *scene, int i, int j)
{
	t_point3d	pixel_center;
	t_vec3d		ray_dir;
	t_ray		ray;
	t_color		color;

	pixel_center = get_pixel_center(&scene->cam, i, j);
	ray_dir = vec_sub(pixel_center, scene->cam.pov);
	ray = ray_new(scene->cam.pov, ray_dir);
	color = get_ray_color(scene, &ray);
	return (color);
}

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

void	ft_translation_hook(void *in)
{
	t_param		*param;
	//static bool	changed;

	param = (t_param *)in;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_D))
	// 	move_cam(param->render.scene, vec_new(2,0,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_A))
	// 	move_cam(param->render.scene, vec_new(-2,0,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_W))
	// 	move_cam(param->render.scene, vec_new(0,2,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_S))
	// 	move_cam(param->render.scene, vec_new(0,-2,0)), changed = true;
	// if (mlx_is_key_down(param->mlx, MLX_KEY_UP))
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

void	ft_turn_hook(void *in)
{
	t_param		*param;
	//static bool	changed;

	param = (t_param *)in;
	if (mlx_is_key_down(param->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(param->mlx);
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
	t_param			param;
	t_scene			scene;
	mlx_image_t*	image;
	t_render		r[THREAD_NO];
	int				i;

	if (argc != 2)
		return (EXIT_FAILURE);
	i = 0;
	parse(&scene, (char *)argv[1]);
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
	mlx_loop_hook(param.mlx, ft_turn_hook, &param);
	mlx_loop(param.mlx);
	mlx_terminate(param.mlx);
	return (EXIT_SUCCESS);
}

