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

static double	hit_cyl_wall(t_cylinder *cy, t_ray *ray)
{
	double	t;
	t_vec3d	x;
	double	a;
	double	half_b;
	double	c;
	double	disc;
	double	m;

	x = vec_sub(ray->origin, cy->pos);
	a = vec_sqr_len(ray->dir) - vec_dot(ray->dir, cy->dir) * vec_dot(ray->dir, cy->dir);
	half_b = vec_dot(ray->dir, x) - vec_dot(ray->dir, cy->dir) * vec_dot(x, cy->dir);
	c = vec_sqr_len(x) - vec_dot(x, cy->dir) * vec_dot(x, cy->dir) - cy->diam * cy->diam / 4;
	disc = half_b * half_b -  a * c;
	if (disc < 0.)
		return (-1.0);
	t = (-half_b - sqrt(disc)) / a;
	m = vec_dot(ray->dir, vec_scale(cy->dir, t)) + vec_dot(x, cy->dir);
	if (fabs(m) > cy->height / 2)
		return (-1.0);
	return (t);
}

static int	find_smallest_pos_t(double *t)
{
	int	i;
	int	smallest_pos;

	i = 0;
	smallest_pos = -1;
	while (i < 3)
	{
		if (t[i] < 0.)
		{
			i++;
			continue;
		}
		if (smallest_pos < 0)
			smallest_pos = i;
		else if (t[smallest_pos] > t[i])
			smallest_pos = i;
		i++;
	}
	return (smallest_pos);
}

static void	get_surf_norm_cyl(t_cylinder *cy, t_ray *ray, double t, t_vec3d *norm)
{
	t_vec3d	x;
	double	m;
	t_vec3d	p;

	x = vec_sub(ray->origin, cy->pos);
	m = vec_dot(ray->dir, vec_scale(cy->dir, t)) + vec_dot(x, cy->dir);
	p = ray_at(ray, t);
	*norm = vec_norm(vec_sub(p, vec_sub(cy->pos, vec_scale(cy->dir, m))));
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray, t_vec3d *norm)
{
	t_plane	d[2];
	double	t[3];
	int		i;

	t[0] = hit_disk(&(t_plane){.type = PLANE, .dir = cy->dir,
		.pos = vec_add(cy->pos, vec_scale(cy->dir, cy->height / 2))},
		ray, cy->diam / 2);
	t[1] = hit_disk(&(t_plane){.type = PLANE, .dir = cy->dir,
		.pos = vec_add(cy->pos, vec_scale(cy->dir, -(cy->height / 2)))},
		ray, cy->diam / 2);
	t[2] = hit_cyl_wall(cy, ray);

	i = find_smallest_pos_t(t);
	if (i == -1)
		return (-1.0);
	else if (i < 2)
	{
		if (norm)
			*norm = cy->dir;
	}
	else if (i == 2)
	{
		if (norm)
			get_surf_norm_cyl(cy, ray, t[2], norm);
	}
	return (t[i]);
}
