/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:20 by flauer            #+#    #+#             */
/*   Updated: 2023/11/27 16:17:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "ray.h"
#include "hit.h"

double	hit_sphere(t_obj *obj, t_ray *ray, t_vec3d *const norm)
{
	double	abc[3];
	double	t;
	double	disc;
	t_vec3d	oc;

	oc = vec_sub(ray->origin, obj->pos);
	abc[0] = vec_sqr_len(ray->dir);
	abc[1] = vec_dot(oc, ray->dir);
	abc[2] = vec_sqr_len(oc) - (obj->sp.diameter * obj->sp.diameter / 4);
	disc = abc[1] * abc[1] - abc[0] * abc[2];
	if (disc < 0)
		return (-1.0);
	else
	{
		t = (-abc[1] - sqrt(disc)) / abc[0];
		*norm = vec_norm(vec_sub(ray_at(ray, t), obj->pos));
		return (t);
	}
}
