#ifndef HIT_H
# define HIT_H

typedef struct s_hitrec
{
	t_point3d	p;
	t_vec3d		normal;
	double		t;
	t_obj		*obj;
}	t_hitrec;

bool	hit_objects(t_scene *scene, t_ray *ray, t_hitrec *hitrec);

double	hit_sphere(t_sphere *sp, t_ray *ray, t_vec3d *norm);
double	hit_plane(t_plane *pl, t_ray *ray, t_vec3d *norm);
double	hit_cylinder(t_cylinder *cy, t_ray *ray, t_vec3d *norm);

#endif
