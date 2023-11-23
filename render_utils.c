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

t_color	get_diffuse_light(t_color *obj_color, double angle, t_obj *obj)
{
	return ((t_color){
		.r = obj_color->r * angle * obj->light.brightness * obj->color.r,
		.g = obj_color->g * angle * obj->light.brightness * obj->color.g,
		.b = obj_color->b * angle * obj->light.brightness * obj->color.b,
	});
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
