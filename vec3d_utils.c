/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:16:09 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 16:16:09 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "MLX42.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"

bool	vec_equal(const t_vec3d v, const t_vec3d w)
{
	return ((v.x == w.x) && (v.y == w.y) && (v.z == w.z));
}

double	vec_dist(const t_point3d p, const t_point3d q)
{
	return (vec_len(vec_sub(p, q)));
}
