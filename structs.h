#ifndef STRUCTS_H
# define STRUCTS_H

# include "colors.h"

typedef struct s_amb
{
	int		type;
	double	ratio;
	t_color	color;
}	t_amb;

typedef struct	s_cam
{
	int		type;
	t_vec3d	pov;
	t_vec3d	orientation;
	uint8_t	fov;
}	t_cam;

typedef struct	s_light
{
	int		type;
	t_vec3d	pos;
	double	brightness;
	t_color	color;
}	t_light;


typedef struct	s_minirt {

}	t_minirt;

#endif
