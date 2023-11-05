#ifndef STRUCTS_H
# define STRUCTS_H

# include "colors.h"
# include "vec3d.h"

typedef enum e_type
{
	LIGHT = 1 << 0,
	SPHERE = 1 << 1,
	PLANE = 1 << 2,
	CYLINDER = 1 << 3,
}	t_type;

typedef struct s_amb
{
	double		ratio;
	t_color		color;
	bool		set;
}	t_amb;

typedef struct	s_cam
{
	t_point3d	pov;
	t_vec3d		dir;
	uint8_t		fov;
	int			foc;
	bool		set;
	t_vec3d		delta_u;
	t_vec3d		delta_v;
	t_vec3d		pixel_ul;
}	t_cam;

typedef struct	s_obj
{
	t_type		type;
}	t_obj;

typedef struct	s_light
{
	t_type		type;
	t_point3d	pos;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct	s_sphere
{
	t_type		type;
	t_point3d	pos;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct	s_plane
{
	t_type		type;
	t_point3d	pos;
	t_vec3d		dir;
	t_color		color;
}	t_plane;


typedef struct	s_cylinder
{
	t_type		type;
	t_point3d	pos;
	t_vec3d		dir;
	double		diam;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct	s_scene
{
	t_amb	amb;
	t_cam	cam;
	t_list	*lights;
	t_list	*objects;
}	t_scene;

#endif
