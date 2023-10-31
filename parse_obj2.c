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
