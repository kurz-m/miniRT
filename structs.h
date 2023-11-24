#ifndef STRUCTS_H
# define STRUCTS_H

# include "typedefs.h"
# include <pthread.h>
# include "colors.h"

struct	s_color
{
	double	r;
	double	g;
	double	b;
};

struct s_vec3d
{
	double	x;
	double	y;
	double	z;
};

struct s_amb
{
	double		ratio;
	t_color		color;
	bool		set;
};

struct	s_cam
{
	t_point3d	pov;
	t_vec3d		dir;
	uint8_t		fov;
	int			foc;
	bool		set;
	t_vec3d		delta_u;
	t_vec3d		delta_v;
	t_vec3d		pixel_ul;
};
struct s_hitrec
{
	t_point3d	p;
	t_vec3d		normal;
	double		t;
	t_obj		*obj;
	t_ray		*ray;
};

struct	s_parse
{
	t_amb	amb;
	t_cam	cam;
	t_list	*lights;
	t_list	*objects;
};

struct	s_ray {
	t_point3d	origin;
	t_vec3d		dir;
};

struct	s_lumi
{
	t_ray		light_ray;
	t_hitrec	hit_light;
	t_vec3d		norm;
	t_color		color;
};

struct s_render
{
	t_scene		*scene;
	mlx_image_t	*image;
	int			i;
};

struct s_param
{
	mlx_t		*mlx;
	pthread_t	thread[THREAD_NO];
	t_scene		*scene;
	mlx_image_t	*image;
};

enum e_type
{
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
};

struct	s_scene
{
	t_amb	amb;
	t_cam	cam;
	t_obj	*lights;
	int		n_light;
	t_obj	*objs;
	int		n_obj;
};

struct	s_light
{
	double		brightness;
};

struct	s_sphere
{
	double		diameter;
};

struct	s_plane
{
	t_vec3d		dir;
};

struct	s_cylinder
{
	t_vec3d		dir;
	double		diam;
	double		height;
};

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

#endif
