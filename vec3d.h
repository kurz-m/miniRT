#ifndef VEC3D_H
# define VEC3D_H

# include <stdbool.h>

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}	t_vec3d;

typedef t_vec3d	t_point3d;

t_vec3d	vec_add(t_vec3d v, t_vec3d w);

t_vec3d	vec_sub(t_vec3d v, t_vec3d w);

double	vec_dot(t_vec3d v, t_vec3d w);

t_vec3d	vec_cross(t_vec3d v, t_vec3d w);

t_vec3d	vec_norm(t_vec3d v);

double	vec_len(t_vec3d v);

t_vec3d	vec_multiply(t_vec3d v, double scalar);

bool	vec_equal(t_vec3d v, t_vec3d w);

double	vec_dist(t_point3d p, t_point3d q);

#endif
