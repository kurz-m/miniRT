#ifndef STRUCTS_H
# define STRUCTS_H

# include "colors.h"
# include "vec3d.h"
# include "libft.h"

typedef struct s_amb
{
	double		ratio;
	t_color		color;
}	t_amb;

typedef struct	s_cam
{
	t_point3d	pov;
	t_vec3d		dir;
	uint8_t		fov;
}	t_cam;

typedef struct	s_obj
{
	int			type;
}	t_obj;

typedef struct	s_light
{
	int			type;
	t_point3d	pos;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct	s_sphere
{
	int			type;
	t_point3d	pos;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct	s_plane
{
	int			type;
	t_point3d	pos;
	t_vec3d		dir;
	t_color		color;
}	t_plane;


typedef struct	s_cylinder
{
	int			type;
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
