#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

double	hit_plane(t_plane *pl, t_ray *ray, t_vec3d *norm)
{
	double	denom;
	double	t;
	t_vec3d	temp;

	denom = vec_dot(pl->dir, ray->direction);
	if (denom > 1e-6)
	{
		temp = vec_sub(pl->pos, ray->origin);
		t = vec_dot(temp, pl->dir) / denom;
		if (norm)
			*norm = pl->dir;
		return (t);
	}
	return (-1.0);
}
