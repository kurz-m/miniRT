#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

uint32_t	get_rgba(int r, int g, int b, int a);
uint32_t	get_rgba_from_tcol(t_color col);
t_color		color_new(int r, int g, int b);
t_color		color_scale(t_color col, double scale);
t_color		color_add(t_color col1, t_color col2);

#endif
