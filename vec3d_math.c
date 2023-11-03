#include "libft.h"
#include "vec3d.h"
#include <math.h>

t_vec3d	vec_new(double x, double y, double z)
{
	t_vec3d		new;

	new = (t_vec3d){
		.x = x,
		.y = y,
		.z = z,
	};
	return (new);
}

t_vec3d	vec_add(t_vec3d v, t_vec3d w)
{
	t_vec3d		vector;

	vector = (t_vec3d){
		.x = v.x + w.x,
		.y = v.y + w.y,
		.z = v.z + w.z,
	};
	return (vector);
}

t_vec3d	vec_sub(t_vec3d v, t_vec3d w)
{
	t_vec3d		vector;

	vector = (t_vec3d){
		.x = v.x - w.x,
		.y = v.y - w.y,
		.z = v.z - w.z,
	};
	return (vector);
}

double	vec_dot(t_vec3d v, t_vec3d w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vec3d	vec_cross(t_vec3d v, t_vec3d w)
{
	t_vec3d		vector;

	vector = (t_vec3d){
		.x = v.y * w.z - v.z * w.y,
		.y = v.z * w.x - v.x * w.z,
		.z = v.x * w.y - v.y * w.x,
	};
	return (vector);
}

double	vec_len(t_vec3d v)
{
	return (sqrt(vec_dot(v, v)));
}

t_vec3d	vec_scale(t_vec3d v, double scalar)
{
	t_vec3d		vector;

	vector = (t_vec3d){
		.x = v.x * scalar,
		.y = v.y * scalar,
		.z = v.z * scalar,
	};
	return (vector);
}

t_vec3d	vec_norm(t_vec3d v)
{
	return (vec_scale(v, 1.0 / vec_len(v)));
}

bool	vec_equal(t_vec3d v, t_vec3d w)
{
	return ((v.x == w.x) && (v.y == w.y) && (v.z == w.z));
}

double	vec_dist(t_point3d p, t_point3d q)
{
	return (vec_len(vec_sub(p, q)));
}
