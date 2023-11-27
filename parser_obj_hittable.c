#include <math.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "parse.h"
#include "utils.h"

bool	parse_sphere(t_parse *p, char **args)
{
	t_obj	o;
	t_obj	*sp;

	if (ft_arrlen(args) != 5)
		return (ft_error3(args, BAD_NUM_ARGS));
	o.type = SPHERE;
	if (!parse_vec(&o.pos, args[1]))
		return (ft_error("sphere pos", args[1], BAD_VEC));
	if (!parse_double(&o.sp.diameter, args[2], 0, INFINITY))
		return (ft_error("sphere diameter", args[2], BAD_DOUBLE));
	if (!parse_color(&o.color, args[3], &o.s, args[4]))
		return (ft_error("bad sphere definition!", NULL, NULL));
	sp = malloc(sizeof(t_obj));
	if (!sp)
		return (ft_error(MALLOC_ERR, NULL, NULL));
	*sp = (t_obj){.color = o.color, .sp.diameter = o.sp.diameter,
		.pos = o.pos, .type = o.type, .s = o.s};
	ft_lstadd_back(&(p->objects), ft_lstnew(sp));
	return (true);
}

bool	parse_plane(t_parse *p, char **args)
{
	t_obj	o;
	t_obj	*pl;

	if (ft_arrlen(args) != 5)
		return (ft_error3(args, BAD_NUM_ARGS));
	o.type = PLANE;
	if (!parse_vec(&o.pos, args[1]))
		return (ft_error("plane pos", args[1], BAD_VEC));
	if (!parse_norm_vec(&o.pl.dir, args[2]))
		return (ft_error("plane direction", args[2], BAD_VEC));
	if (!parse_color(&o.color, args[3], &o.s, args[4]))
		return (ft_error("bad plane definition", NULL, NULL));
	pl = malloc(sizeof(t_obj));
	if (!pl)
		return (ft_error(MALLOC_ERR, NULL, NULL));
	*pl = (t_obj){.color = o.color, .pl.dir = o.pl.dir,
		.pos = o.pos, .type = o.type, .s = o.s};
	ft_lstadd_back(&(p->objects), ft_lstnew(pl));
	return (true);
}

bool	parse_cylinder(t_parse *p, char **args)
{
	t_obj	o;
	t_obj	*cy;

	if (ft_arrlen(args) != 7)
		return (ft_error3(args, BAD_NUM_ARGS));
	o.type = CYLINDER;
	if (!parse_vec(&o.pos, args[1]))
		return (ft_error("cylinder pos", args[1], BAD_VEC));
	if (!parse_norm_vec(&o.cy.dir, args[2]))
		return (ft_error("cylinder direction", args[2], BAD_VEC));
	if (!parse_double(&o.cy.diam, args[3], 0, INFINITY))
		return (ft_error("cylinder diameter", args[3], BAD_DOUBLE));
	if (!parse_double(&o.cy.height, args[4], 0, INFINITY))
		return (ft_error("cylinder height", args[4], BAD_DOUBLE));
	if (!parse_color(&o.color, args[5], &o.s, args[6]))
		return (ft_error("bad cylinder definition", NULL, NULL));
	cy = malloc(sizeof(t_obj));
	if (!cy)
		return (ft_error(MALLOC_ERR, NULL, NULL));
	*cy = (t_obj){.color = o.color, .cy.dir = o.cy.dir,
		.pos = o.pos, .type = o.type, .cy.diam = o.cy.diam,
		.cy.height = o.cy.height, .s = o.s};
	ft_lstadd_back(&(p->objects), ft_lstnew(cy));
	return (true);
}
