#include <math.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"

double	vec_dot(const t_vec3d v, const t_vec3d w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vec3d	vec_cross(const t_vec3d v, const t_vec3d w)
{
	return ((t_vec3d){
		.x = v.y * w.z - v.z * w.y,
		.y = v.z * w.x - v.x * w.z,
		.z = v.x * w.y - v.y * w.x,
	});
}

t_vec3d	vec_norm(const t_vec3d v)
{
	return (vec_scale(v, 1.0 / vec_len(v)));
}

double	vec_sqr_len(const t_vec3d v)
{
	return (vec_dot(v, v));
}
