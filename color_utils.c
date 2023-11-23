#include <stdint.h>
#include <stdbool.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "colors.h"

uint32_t	get_rgba_from_tcol(t_color col)
{
	return (get_rgba(col.r * 255, col.g * 255, col.b * 255, 255));
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	color_new(double r, double g, double b)
{
	return ((t_color){.r = r, .g = g, .b = b});
}

t_color	color_scale(t_color col, double scale)
{
	return ((t_color){
		.r = col.r * scale,
		.g = col.g * scale,
		.b = col.b * scale,
	});
}

t_color	color_add(t_color col1, t_color col2)
{
	return ((t_color){
		.r = col1.r + col2.r,
		.g = col1.g + col2.g,
		.b = col1.b + col2.b
	});
}
