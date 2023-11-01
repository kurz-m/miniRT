#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef struct	s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

uint32_t	get_rgba(int r, int g, int b, int a);

#endif
