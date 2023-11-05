#include <math.h>
#include "libft.h"
#include "vec3d.h"

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

double	vec_len(t_vec3d v)
{
	return (sqrt(vec_dot(v, v)));
}
