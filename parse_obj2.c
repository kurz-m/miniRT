#include "libft.h"
#include "miniRT.h"

bool	parse_sphere(t_scene *scene, char **args)
{
	t_sphere	s;
	t_sphere	*sp;

	if (ft_arrlen(args) != 4)
		return (free_arr(args), ft_error3(args, BAD_SP));
	s.type = SPHERE;
	if (!parse_vec(&s.pos, args[1]))
		return (free_arr(args), ft_error("sphere pos", args[1], BAD_VEC));
	if (!parse_double(&s.diameter, args[2], 0, INFINITY))
		return (free_arr(args), ft_error("sphere diameter", args[2], BAD_DOUBLE));
	if (!parse_color(&s.color, args[3]))
		return (free_arr(args), ft_error("sphere color", args[3], BAD_COL));
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (free_arr(args), ft_error(MALLOC_ERR, NULL, NULL));
	*sp = (t_sphere){.color = s.color, .diameter = s.diameter,
		.pos = s.pos, .type = s.type};
	ft_lstadd_back(&scene->objects, ft_lstnew(sp));
	free_arr(args);
	return (true);
}

bool	parse_plane(t_scene *scene, char **args)
{
	t_plane	p;
	t_plane	*pl;

	if (ft_arrlen(args) != 4)
		return (free_arr(args), ft_error3(args, BAD_PL));
	p.type = PLANE;
	if (!parse_vec(&p.pos, args[1]))
		return (free_arr(args), ft_error("plane pos", args[1], BAD_VEC));
	if (!parse_vec(&p.dir, args[2]))
		return (free_arr(args), ft_error("plane direction", args[2], BAD_VEC));
	if (!parse_color(&p.color, args[3]))
		return (free_arr(args), ft_error("plane color", args[3], BAD_COL));
	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (free_arr(args), ft_error(MALLOC_ERR, NULL, NULL));
	*pl = (t_plane){.color = p.color, .dir = p.dir,
		.pos = p.pos, .type = p.type};
	ft_lstadd_back(&scene->objects, ft_lstnew(pl));
	free_arr(args);
	return (true);
}

bool	parse_cylinder(t_scene *scene, char **args)
{
	t_cylinder	p;
	t_cylinder	*pl;

	if (ft_arrlen(args) != 6)
		return (free_arr(args), ft_error3(args, BAD_CY));
	p.type = CYLINDER;
	if (!parse_vec(&p.pos, args[1]))
		return (free_arr(args), ft_error("cylinder pos", args[1], BAD_VEC));
	if (!parse_vec(&p.dir, args[2]))
		return (free_arr(args), ft_error("cylinder direction", args[2], BAD_VEC));
	if (!parse_double(&p.diam, args[3], 0, INFINITY))
		return (free_arr(args), ft_error("cylinder diameter", args[3], BAD_DOUBLE));
	if (!parse_double(&p.height, args[4], 0, INFINITY))
		return (free_arr(args), ft_error("cylinder height", args[4], BAD_DOUBLE));
	if (!parse_color(&p.color, args[5]))
		return (free_arr(args), ft_error("cylinder color", args[5], BAD_COL));
	pl = malloc(sizeof(t_cylinder));
	if (!pl)
		return (free_arr(args), ft_error(MALLOC_ERR, NULL, NULL));
	*pl = (t_cylinder){.color = p.color, .dir = p.dir,
		.pos = p.pos, .type = p.type, .diam = p.diam, .height = p.height};
	ft_lstadd_back(&scene->objects, ft_lstnew(pl));
	free_arr(args);
	return (true);
}
