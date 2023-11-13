#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

double	hit_sphere(t_obj *obj, t_ray *ray, t_vec3d *norm)
{
	t_list		*objects;
	double		t;

	t_vec3d	oc = vec_sub(ray->origin, obj->pos);
	double a = vec_sqr_len(ray->dir);
	double half_b = vec_dot(oc, ray->dir);
	double c = vec_sqr_len(oc) - (obj->sp.diameter * obj->sp.diameter / 4);
	double disc = half_b * half_b -  a * c;

	if (disc < 0)
		return (-1.0);
	else
	{
		t = (-half_b - sqrt(disc)) / a;
		*norm = vec_norm(vec_sub(ray_at(ray, t), obj->pos));
		return (t);
	}
}
