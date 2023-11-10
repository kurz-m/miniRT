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
	double	t[3];

	d[0].type = PLANE;
	d[1].type = PLANE;
	d[0].dir = cy->dir;
	d[0].pos = vec_add(cy->pos, vec_scale(cy->dir, cy->height / 2));
	d[1].dir = cy->dir;
	d[1].pos = vec_add(cy->pos, vec_scale(cy->dir, -(cy->height / 2)));

	if (norm)
		*norm = cy->dir;
	t[0] = hit_disk(d, ray, cy->diam / 2);
	t[1] = hit_disk(d + 1, ray, cy->diam / 2);

	t_vec3d x = vec_sub(ray->origin, cy->pos);
	double a = vec_sqr_len(ray->dir) - vec_dot(ray->dir, cy->dir) * vec_dot(ray->dir, cy->dir);
	double half_b = vec_dot(ray->dir, x) - vec_dot(ray->dir, cy->dir) * vec_dot(x, cy->dir);
	double c = vec_sqr_len(x) - vec_dot(x, cy->dir) * vec_dot(x, cy->dir) - cy->diam * cy->diam / 4;
	double disc = half_b * half_b -  a * c;
	if (disc >= 0.)
		t[2] = (-half_b - sqrt(disc)) / a;
	else
		t[2] = INFINITY;
	if (t[0] == -1.0)
		t[0] = INFINITY;
	if (t[1] == -1.0)
		t[1] = INFINITY;
	if (t[2] < INFINITY && t[2] <= t[0] && t[2] <= t[1])
	{
		double m = vec_dot(ray->dir, vec_scale(cy->dir, t[2])) + vec_dot(x, cy->dir);
		t_vec3d p = ray_at(ray, t[2]);
		if (norm)
			*norm = vec_norm(vec_sub(p, vec_sub(cy->pos, vec_scale(cy->dir, m))));
			// *norm = vec_new(1,0,0);
		return (t[2]);
	}
	if (t[0] < INFINITY && t[0] <= t[1])
		return (t[0]);
	if (t[1] < INFINITY)
		return (t[1]);

	return (-1.);

}
