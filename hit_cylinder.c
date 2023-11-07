#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

static double	hit_disk(t_plane *pl, t_ray *ray, double radius)
{
	double	t;

	t = hit_plane(pl, ray, NULL);
	if (t >= 0)
	{
		t_vec3d	p = ray_at(ray, t);
		t_vec3d	v = vec_sub(p, pl->pos);
		double	d2 = vec_sqr_len(v);
		if (d2 <= radius * radius)
			return (t);
	}
	return (-1.0);
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray, t_vec3d *norm)
{
	t_plane	d[2];
	double	t;

	d[0].type = PLANE;
	d[1].type = PLANE;
	d[0].dir = cy->dir;
	d[0].pos = vec_add(cy->pos, vec_scale(cy->dir, cy->height / 2));
	d[1].dir = cy->dir;
	d[1].pos = vec_add(cy->pos, vec_scale(cy->dir, -(cy->height / 2)));

	if (norm)
		*norm = cy->dir;

	t = hit_disk(d, ray, cy->diam / 2);
	if (t > 0)
		return (t);
	t = hit_disk(d + 1, ray, cy->diam / 2);
	if (t > 0)
		return (t);
	return (-1.);
}
