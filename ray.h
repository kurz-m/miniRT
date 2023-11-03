#ifndef RAY_H
# define RAY_H

typedef struct	s_ray {
	t_point3d	origin;
	t_vec3d		direction;
}	t_ray;

t_ray		ray_new(t_point3d origin, t_vec3d dir);
t_point3d	ray_at(t_ray *ray, double t);

#endif
