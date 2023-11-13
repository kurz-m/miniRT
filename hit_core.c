#include "libft.h"
#include "structs.h"
#include <math.h>
#include "vec3d.h"
#include "ray.h"
#include "hit.h"
#include "miniRT.h"

bool	hit_objects(t_scene *scene, t_ray *ray, t_hitrec *hitrec)
{
	int		i;
	double	t;
	t_vec3d	norm;

	norm = vec_new(0, 0, 0);
	hitrec->t = INFINITY;
	while (i < scene->n_obj)
	{
		if (scene->objs[i].u.type == SPHERE)
			t = hit_sphere(&(scene->objs[i].sp), ray, &norm);
		else if (scene->objs[i].u.type == CYLINDER)
			t = hit_cylinder(&(scene->objs[i].cy), ray, &norm);
		else if (scene->objs[i].u.type == PLANE)
			t = hit_plane(&(scene->objs[i].pl), ray, &norm);
		if (0.0 < t && t < hitrec->t)
		{
			hitrec->t = t;
			hitrec->obj = &(scene->objs[i]);
			hitrec->p = ray_at(ray, t);
			hitrec->normal = norm;
		}
		++i;
	}
	if (hitrec->t == INFINITY)
		return (false);
	return (true);
}
