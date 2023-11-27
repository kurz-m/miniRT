/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:19:21 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 16:19:22 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "colors.h"

/// @brief Utility function to combine 4 separate rgba values into
/// a single uint32.
/// @param r Red value.
/// @param g Green value.
/// @param b Blue value.
/// @param a Alpha level.
/// @return Returns a uint32 where each component occupies 8 bits.
static uint32_t	get_rgba(const int r, const int g, const int b, const int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_rgba_from_tcol(const t_color col)
{
	return (get_rgba(col.r * 255, col.g * 255, col.b * 255, 255));
}

t_color	color_new(const double r, const double g, const double b)
{
	return ((t_color){.r = r, .g = g, .b = b});
}

t_color	color_scale(const t_color col, const double scale)
{
	return ((t_color){
		.r = col.r * scale,
		.g = col.g * scale,
		.b = col.b * scale,
	});
}

t_color	color_add(const t_color col1, const t_color col2)
{
	return ((t_color){
		.r = col1.r + col2.r,
		.g = col1.g + col2.g,
		.b = col1.b + col2.b
	});
}
