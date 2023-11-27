/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:55 by flauer            #+#    #+#             */
/*   Updated: 2023/11/27 16:17:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "ray.h"

t_ray	ray_new(t_point3d origin, t_vec3d dir)
{
	t_ray	ray;

	ray = (t_ray){
		.origin = origin,
		.dir = vec_norm(dir),
	};
	return (ray);
}

t_point3d	ray_at(const t_ray *ray, const double t)
{
	return (vec_add(ray->origin, vec_scale(ray->dir, t)));
}
