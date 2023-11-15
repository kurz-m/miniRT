#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

double	hit_plane(t_obj *obj, t_ray *ray, t_vec3d *norm)
{
	double	denom;
	double	t;
	t_vec3d	temp;

	denom = vec_dot(obj->pl.dir, ray->dir);
	if (fabs(denom) > 1e-6)
	{
		temp = vec_sub(obj->pos, ray->origin);
		t = vec_dot(temp, obj->pl.dir) / denom;
		if (vec_dot(ray->dir, obj->pl.dir) >= 0 && norm)
			*norm = vec_scale(obj->pl.dir, -1.);
		else if (norm)
			*norm = obj->pl.dir;
		return (t);
	}
	return (-1.0);
}
