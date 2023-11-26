#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "MLX42.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

bool	hit_objects(t_scene *scene, t_ray *ray, t_hitrec *hitrec)
{
	int		i;
	double	t;
	t_vec3d	norm;

	norm = vec_new(0, 0, 0);
	hitrec->t = INFINITY;
	i = 0;
	while (i < scene->n_obj)
	{
		t = scene->objs[i].hit(&(scene->objs[i]), ray, &norm);
		if (T_MIN < t && t < hitrec->t)
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
