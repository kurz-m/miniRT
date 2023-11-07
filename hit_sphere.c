#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

double	hit_sphere(t_scene *scene, t_ray *ray)
{
	t_list		*objects;
	t_sphere	*sp;

	objects = (t_list *)scene->objects;
	sp = (t_sphere *)objects->content;
	t_vec3d	oc = vec_sub(ray->origin, sp->pos);
	double a = vec_sqr_len(ray->direction);
	double half_b = vec_dot(oc, ray->direction);
	double c = vec_sqr_len(oc) - (sp->diameter * sp->diameter / 4);
	double disc = half_b * half_b -  a * c;

	if (disc < 0)
	{
		return (-1.0);
	}
	else
	{
		return ((-half_b - sqrt(disc)) / a);
	}
}
