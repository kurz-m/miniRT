#include "libft.h"
#include "MLX42.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"

bool	vec_equal(t_vec3d v, t_vec3d w)
{
	return ((v.x == w.x) && (v.y == w.y) && (v.z == w.z));
}

double	vec_dist(t_point3d p, t_point3d q)
{
	return (vec_len(vec_sub(p, q)));
}
