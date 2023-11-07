#include "libft.h"
#include "structs.h"
#include <math.h>
#include "vec3d.h"
#include "ray.h"
#include "hit.h"
#include <stdio.h>
#include "miniRT.h"

bool	hit_objects(t_scene *scene, t_ray *ray, t_hitrec *hitrec)
{
	t_list	*obj;
	t_obj	*curr_obj;
	double	t;
	t_vec3d	norm;

	norm = vec_new(0, 0, 0);
	hitrec->t = INFINITY;
	obj = scene->objects;
	while (obj)
	{
		curr_obj = obj->content;
		if (curr_obj->type == SPHERE)
			t = hit_sphere((t_sphere *)curr_obj, ray, &norm);
		else if (curr_obj->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)curr_obj, ray, &norm);
		else if (curr_obj->type == PLANE)
			t = hit_plane((t_plane *)curr_obj, ray, &norm);
		if (0.0 < t < hitrec->t)
		{
			hitrec->t = t;
			hitrec->obj = curr_obj;
			hitrec->p = ray_at(ray, t);
			hitrec->normal = norm;
		}
		obj = obj->next;
	}
	if (hitrec->t == INFINITY)
		return (false);
	return (true);
}
