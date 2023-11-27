/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:19:16 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 16:19:17 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "colors.h"

// ambient color model: the ambient color vector is used as a scale for the 
// obj color. 
// see here https://learnwebgl.brown37.net/09_lights/lights_ambient.html
t_color	get_ambient_color(const t_scene *sc, const t_hitrec *hit)
{
	return ((t_color){
		.r = hit->obj->color.r * sc->amb.color.r * sc->amb.ratio,
		.g = hit->obj->color.g * sc->amb.color.g * sc->amb.ratio,
		.b = hit->obj->color.b * sc->amb.color.b * sc->amb.ratio,
	});
}

t_color	get_background_color(const t_ray *ray)
{
	t_vec3d	unit_direction;
	double	a;
	t_color	start_col;
	t_color	end_col;

	unit_direction = vec_norm(ray->dir);
	a = 0.5 * (unit_direction.y + 1.0);
	start_col = color_scale(color_new(1, 1, 1), (1.0 - a));
	end_col = color_scale(color_new(0, 0, 1), a);
	return (color_add(start_col, end_col));
}

void	color_clamp(t_color *color)
{
	if (color->r > 1.0)
		color->r = 1.0;
	if (color->g > 1.0)
		color->g = 1.0;
	if (color->b > 1.0)
		color->b = 1.0;
}
