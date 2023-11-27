#include <stdbool.h>
#include <math.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "colors.h"
#include "ray.h"
#include "hit.h"

/**
 * @brief Utility function to calculate the hit point with a disk.
 * 
 * @param obj The current object.
 * @param ray The current ray.
 * @param radius The radius of the cone.
 * @return double Calculated t for the ray formula: P(i) = A + t * dir
 */
static double	hit_disk(t_obj *obj, t_ray *ray, const double radius)
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

/**
 * @brief Utility function to calculate the hit point with the cone wall.
 * 
 * @param obj The current object.
 * @param ray The current ray.
 * @return double Calculated t for the ray formula: P(i) = A + t * dir
 */
static double	hit_cone_wall(t_obj *obj, t_ray *ray)
{
	double	t;
	t_vec3d	x;
	double	abcm[4];
	double	disc;
	double	wall_dot[2];

	x = vec_sub(ray->origin, obj->pos);
	wall_dot[0] = vec_dot(ray->dir, obj->co.dir);
	wall_dot[1] = vec_dot(x, obj->co.dir);
	abcm[0] = vec_sqr_len(ray->dir) - wall_dot[0] * wall_dot[0]
		* (1 + pow(obj->co.angle, 2));
	abcm[1] = vec_dot(ray->dir, x) - wall_dot[0] * wall_dot[1]
		* (1 + pow(obj->co.angle, 2));
	abcm[2] = vec_sqr_len(x) - wall_dot[1] * wall_dot[1]
		* (1 + pow(obj->co.angle, 2));
	disc = abcm[1] * abcm[1] - abcm[0] * abcm[2];
	if (disc < 0.)
		return (-1.0);
	t = (-abcm[1] - sqrt(disc)) / abcm[0];
	abcm[3] = vec_dot(ray->dir, vec_scale(obj->co.dir, t))
		+ vec_dot(x, obj->co.dir);
	if (abcm[3] > obj->co.max_m || abcm[3] < obj->co.min_m)
		return (-1.0);
	return (t);
}

/**
 * @brief Utility function to check for the closes hit point
 * of the ray with the given cone.
 * 
 * @param t Calculated t for the ray formula: P(i) = A + t * dir
 * @return int -1 if given t is bigger than current smallest t, otherwise
 * given t.
 */
static int	find_smallest_pos_t(const double *t)
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

/**
 * @brief Function for calculating the norm vector to the cone surface.
 * 
 * @param obj The current cone object.
 * @param ray The current ray.
 * @param t The position of the ray at position t.
 * @param norm Norm vector given as reference.
 */
static void	get_cone_norm(t_obj *obj, t_ray *ray, double t, t_vec3d *const norm)
{
	t_vec3d	x;
	double	m;
	t_vec3d	p;

	x = vec_sub(ray->origin, obj->pos);
	m = vec_dot(ray->dir, vec_scale(obj->co.dir, t)) + vec_dot(x, obj->co.dir);
	p = ray_at(ray, t);
	*norm = vec_norm(vec_sub(vec_sub(p, obj->pos), vec_scale(obj->co.dir,
		m * (1 + pow(obj->co.angle, 2)))));
}

double	hit_cone(t_obj *obj, t_ray *ray, t_vec3d *const norm)
{
	double	t[3];
	int		i;
	t_obj	d[2];

	d[0] = (t_obj){.type = PLANE, .pl.dir = obj->co.dir,
		.pos = vec_add(obj->pos, vec_scale(obj->co.dir, obj->co.min_m))};
	t[0] = hit_disk(&d[0], ray, obj->co.angle * obj->co.min_m);
	d[1] = (t_obj){.type = PLANE, .pl.dir = obj->co.dir,
		.pos = vec_add(obj->pos, vec_scale(obj->co.dir, obj->co.max_m))};
	t[1] = hit_disk(&d[1], ray, obj->co.angle * obj->co.max_m);
	t[2] = hit_cone_wall(obj, ray);
	i = find_smallest_pos_t(t);
	if (i == -1)
		return (-1.0);
	else if (i == 0)
		*norm = obj->co.dir;
	else if (i == 1)
		*norm = vec_scale(obj->co.dir, -1.);
	else if (i == 2)
		get_cone_norm(obj, ray, t[2], norm);
	return (t[i]);
}
