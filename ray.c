#include "vec3d.h"
#include "ray.h"

t_ray		ray_new(t_point3d origin, t_vec3d dir)
{
	t_ray	ray;

	ray = (t_ray){
		.origin = origin,
		.direction = dir,
	};
	return (ray);
}

t_point3d	ray_at(t_ray *ray, double t)
{
	return (vec_add(ray->origin, vec_scale(ray->direction, t)));
}