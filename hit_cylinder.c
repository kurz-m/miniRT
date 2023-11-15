#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

static double	hit_disk(t_obj *obj, t_ray *ray, double radius)
{
	double	t;
	t_vec3d	norm;
	t_vec3d	p;
	t_vec3d	v;
	double	d2;

	t = hit_plane(obj, ray, &norm);
	if (t >= 0)
	{
		p = ray_at(ray, t);
		v = vec_sub(p, obj->pos);
		d2 = vec_sqr_len(v);
		if (d2 <= radius * radius)
			return (t);
	}
	return (-1.0);
}

static double	hit_cyl_wall(t_obj *obj, t_ray *ray)
{
	double	t;
	t_vec3d	x;
	double	abc[3];
	double	disc;
	double	m;

	x = vec_sub(ray->origin, obj->pos);
	abc[0] = vec_sqr_len(ray->dir) - vec_dot(ray->dir, obj->cy.dir)
		* vec_dot(ray->dir, obj->cy.dir);
	abc[1] = vec_dot(ray->dir, x) - vec_dot(ray->dir, obj->cy.dir)
		* vec_dot(x, obj->cy.dir);
	abc[2] = vec_sqr_len(x) - vec_dot(x, obj->cy.dir) * vec_dot(x, obj->cy.dir)
		- obj->cy.diam * obj->cy.diam / 4;
	disc = abc[1] * abc[1] - abc[0] * abc[2];
	if (disc < 0.)
		return (-1.0);
	t = (-abc[1] - sqrt(disc)) / abc[0];
	m = vec_dot(ray->dir, vec_scale(obj->cy.dir, t)) + vec_dot(x, obj->cy.dir);
	if (fabs(m) > obj->cy.height / 2)
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
			continue ;
		}
		if (smallest_pos < 0)
			smallest_pos = i;
		else if (t[i] < t[smallest_pos])
			smallest_pos = i;
		i++;
	}
	return (smallest_pos);
}

static void	get_surf_norm_cyl(t_obj *obj, t_ray *ray, double t, t_vec3d *norm)
{
	t_vec3d	x;
	double	m;
	t_vec3d	p;

	x = vec_sub(ray->origin, obj->pos);
	m = vec_dot(ray->dir, vec_scale(obj->cy.dir, t)) + vec_dot(x, obj->cy.dir);
	p = ray_at(ray, t);
	*norm = vec_norm(vec_sub(vec_sub(p, obj->pos), vec_scale(obj->cy.dir, m)));
}

double	hit_cylinder(t_obj *obj, t_ray *ray, t_vec3d *norm)
{
	double	t[3];
	int		i;
	t_obj	d[2];

	d[0] = (t_obj){.type = PLANE, .pl.dir = obj->cy.dir,
		.pos = vec_add(obj->pos, vec_scale(obj->cy.dir, obj->cy.height / 2))};
	t[0] = hit_disk(&d[0], ray, obj->cy.diam / 2);
	d[1] = (t_obj){.type = PLANE, .pl.dir = obj->cy.dir,
		.pos = vec_add(obj->pos, vec_scale(obj->cy.dir, -obj->cy.height / 2))};
	t[1] = hit_disk(&d[1], ray, obj->cy.diam / 2);
	t[2] = hit_cyl_wall(obj, ray);
	i = find_smallest_pos_t(t);
	if (i == -1)
		return (-1.0);
	else if (i == 0)
		*norm = obj->cy.dir;
	else if (i == 1)
		*norm = vec_scale(obj->cy.dir, -1.);
	else if (i == 2)
		get_surf_norm_cyl(obj, ray, t[2], norm);
	return (t[i]);
}
