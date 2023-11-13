#ifndef HIT_H
# define HIT_H

typedef struct s_hitrec
{
	t_point3d	p;
	t_vec3d		normal;
	double		t;
	t_objs		*obj;
}	t_hitrec;

/// @brief Main entry point for calculating intersections between
/// objects and the ray
/// @param scene Main struct holding all the elements
/// @param ray Ray being shot into the scene
/// @param hitrec Structure holding the hit record of the ray
/// @return true if new hit was found, false if not
bool	hit_objects(t_scene *scene, t_ray *ray, t_hitrec *hitrec);

/// @brief Function for calculating intersections with a sphere
/// @param sp The sphere object
/// @param ray Ray being shot into the scene
/// @param norm Surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_sphere(t_sphere *sp, t_ray *ray, t_vec3d *norm);

/// @brief Function for calculating intersections with a plane
/// @param pl The plane object
/// @param ray Ray being shot into the scene
/// @param norm Surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_plane(t_plane *pl, t_ray *ray, t_vec3d *norm);

/// @brief Function for calculating intersections with a cylinder
/// @param sp The cylinder object
/// @param ray Ray being shot into the scene
/// @param norm Surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_cylinder(t_cylinder *cy, t_ray *ray, t_vec3d *norm);

#endif
