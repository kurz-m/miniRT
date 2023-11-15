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

typedef struct	s_light
{
	double		brightness;
}	t_light;

typedef struct	s_sphere
{
	double		diameter;
}	t_sphere;

typedef struct	s_plane
{
	t_vec3d		dir;
}	t_plane;


typedef struct	s_cylinder
{
	t_vec3d		dir;
	double		diam;
	double		height;
}	t_cylinder;

typedef struct s_obj	t_obj;

typedef struct	s_ray {
	t_point3d	origin;
	t_vec3d		dir;
}	t_ray;

struct	s_obj
{
	t_type		type;
	t_color		color;
	t_point3d	pos;
	double		(*hit)(t_obj *obj, t_ray *ray, t_vec3d *norm);
	union
	{
		t_light		light;
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
};

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
	t_obj	*lights;
	int		n_light;
	t_obj	*objs;
	int		n_obj;
}	t_scene;

#endif
