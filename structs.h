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
	t_vec3d		pixel_ul; // center of upper left pixel
}	t_cam;

typedef struct	s_obj
{
	t_type		type;
	t_color		color;
}	t_obj;

typedef struct	s_utils
{
	t_type		type;
	t_color		color;
}	t_utils;


typedef struct	s_light
{
	t_type		type;
	t_color		color;
	t_point3d	pos;
	double		brightness;
}	t_light;

typedef struct	s_sphere
{
	t_type		type;
	t_color		color;
	t_point3d	pos;
	double		diameter;
}	t_sphere;

typedef struct	s_plane
{
	t_type		type;
	t_color		color;
	t_point3d	pos;
	t_vec3d		dir;
}	t_plane;


typedef struct	s_cylinder
{
	t_type		type;
	t_color		color;
	t_point3d	pos;
	t_vec3d		dir;
	double		diam;
	double		height;
}	t_cylinder;

typedef union	u_obj
{
	t_utils		u;
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}	t_objs;

typedef struct	s_parse
{
	t_amb	amb;
	t_cam	cam;
	t_list	*lights;
	t_list	*objects;
}	t_parse;

typedef struct	s_scene
{
	t_amb	amb;
	t_cam	cam;
	t_light	*lights;
	int		n_light;
	t_objs	*objs;
	int		n_obj;
}	t_scene;

#endif
