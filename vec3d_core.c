#include <math.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"

t_vec3d	vec_new(const double x, const double y, const double z)
{
	return ((t_vec3d){
		.x = x,
		.y = y,
		.z = z,
	});
}

t_vec3d	vec_add(const t_vec3d v, const t_vec3d w)
{
	return ((t_vec3d){
		.x = v.x + w.x,
		.y = v.y + w.y,
		.z = v.z + w.z,
	});
}

t_vec3d	vec_sub(const t_vec3d v, const t_vec3d w)
{
	return ((t_vec3d){
		.x = v.x - w.x,
		.y = v.y - w.y,
		.z = v.z - w.z,
	});
}

t_vec3d	vec_scale(const t_vec3d v, const double scalar)
{
	return ((t_vec3d){
		.x = v.x * scalar,
		.y = v.y * scalar,
		.z = v.z * scalar,
	});
}

double	vec_len(const t_vec3d v)
{
	return (sqrt(vec_dot(v, v)));
}
