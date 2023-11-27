/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:51 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 18:22:19 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "libft.h"
#include "MLX42.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "colors.h"
#include "camera.h"
#include "ray.h"
#include "hit.h"
#include "render.h"

t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_hitrec	hitrec;
	t_color		color;

	hitrec.ray = ray;
	color = color_new(0, 0, 0);
	if (hit_objects(scene, ray, &hitrec))
	{
		return (color_add(color, get_obj_lumination(scene, &hitrec)));
	}
	return (get_background_color(ray));
}

static void	create_samples(double *fract)
{
	int		i;
	double	step;

	step = 1.0 / SAMPLES;
	i = 0;
	while (i < SAMPLES)
	{
		fract[i] = 0.5 * step + i * step;
		++i;
	}
}

t_color	get_px_color(t_scene *scene, int i, int j)
{
	t_point3d			pixel_center;
	t_ray				ray;
	t_color				color;
	double				fract[SAMPLES];
	int					km[2];

	create_samples(fract);
	km[0] = 0;
	color = color_new(0, 0, 0);
	while (km[0] < SAMPLES)
	{
		km[1] = 0;
		while (km[1] < SAMPLES)
		{
			pixel_center = get_pixel_center(&scene->cam, i
					+ fract[km[1]], j + fract[km[0]]);
			ray = ray_new(scene->cam.pov, vec_sub(pixel_center,
						scene->cam.pov));
			color = color_add(color, get_ray_color(scene, &ray));
			++km[1];
		}
		++km[0];
	}
	color = color_scale(color, (double)1 / (SAMPLES * SAMPLES));
	return (color);
}
