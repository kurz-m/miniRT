#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "libft.h"
#include "MLX42.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "colors.h"
#include "camera.h"
#include "ray.h"
#include "hit.h"
#include "render.h"

t_color	get_diffuse_light(
	const t_color *obj_color, const double angle, const t_obj *obj)
{
	return ((t_color){
		.r = obj_color->r * angle * obj->light.brightness * obj->color.r,
		.g = obj_color->g * angle * obj->light.brightness * obj->color.g,
		.b = obj_color->b * angle * obj->light.brightness * obj->color.b,
	});
}

/**
 * @brief Utility to get the specular component of the light.
 * 
 * @param hitrec Struct containing parameters of currect hit object.
 * @param l Struct containing the light parameters.
 * @return t_color The scaled color.
 */
static t_color	get_specular(const t_hitrec *hitrec, const t_lumi *l)
{
	t_vec3d	r;
	double	r_dot_v;
	double	n_dot_l;
	double	power;

	n_dot_l = vec_dot(hitrec->normal, l->light_ray.dir);
	r = vec_scale(hitrec->normal, 2.0);
	r = vec_scale(r, n_dot_l);
	r = vec_sub(r, l->light_ray.dir);
	r_dot_v = vec_dot(r, vec_scale(hitrec->ray->dir, -1));
	if (r_dot_v > T_MIN)
	{
		power = pow(r_dot_v / (vec_len(r) * vec_len(hitrec->ray->dir)), 100);
		return (color_scale(color_new(1, 1, 1), power));
	}
	return (color_new(0, 0, 0));
}

t_color	get_obj_lumination(t_scene *scene, t_hitrec *hitrec)
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
			l.color = color_add(l.color, get_specular(hitrec, &l));
			color_clamp(&l.color);
		}
	}
	return (l.color);
}

t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_hitrec	hitrec;
	t_color		color;

	hitrec.ray = ray;
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
