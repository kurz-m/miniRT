#include "libft.h"
#include "structs.h"
#include "parse.h"
#include "error.h"
#include "miniRT.h"
#include <stdbool.h>

bool	parse_ambient(t_parse *p, char **args)
{
	if (p->amb.set)
		return (ft_error(MULT_AMB, NULL, NULL));
	if (ft_arrlen(args) != 3)
		return (ft_error3(args, BAD_AMB));
	if (!parse_color(&p->amb.color, args[2]))
		return (ft_error("ambient", args[2], BAD_COL));
	if (!parse_double(&p->amb.ratio, args[1], 0, 1))
		return (ft_error(args[1], "bad ambient ratio!", NULL));
	p->amb.set = true;
	return (true);
}

bool	parse_cam(t_parse *p, char **args)
{
	if (p->cam.set)
		return (ft_error(MULT_CAM, NULL, NULL));
	if (ft_arrlen(args) != 4)
		return (ft_error3(args, BAD_CAM));
	if (!parse_vec(&p->cam.pov, args[1]))
		return (ft_error("cam position", args[1], BAD_VEC));
	if (!parse_norm_vec(&p->cam.dir, args[2]))
		return (ft_error("cam direction", args[2], BAD_VEC));
	if (!parse_int((int *)&p->cam.fov, args[3], 1, 179))
		return (ft_error(args[3], BAD_FOV, NULL));
	p->cam.foc = get_focal_length(p->cam.fov);
	p->cam.set = true;
	return (true);
}

bool	parse_lights(t_parse *p, char **args)
{
	t_light	l;
	t_light	*nl;

	if (ft_arrlen(args) > 4 || ft_arrlen(args) < 3)
		return (ft_error3(args, BAD_LAMP));
	l = (t_light){};
	l.type = LIGHT;
	l.color = (t_color){.r = 255, .g = 255, .b = 255};
	if (!parse_vec(&l.pos, args[1]))
		return (ft_error("light position", args[1], BAD_VEC));
	if (!parse_double(&l.brightness, args[2], 0, 1))
		return (ft_error("light brightness", args[2], BAD_DOUBLE));
	if (ft_arrlen(args) == 4 && !parse_color(&l.color, args[3]))
		return (ft_error("light color", args[3], BAD_COL));
	nl = malloc(sizeof(t_light));
	if (!nl)
		return (ft_error(MALLOC_ERR, NULL, NULL));
	*nl = (t_light){.type = l.type, .brightness = l.brightness,
		.color = l.color, .pos = l.pos};
	ft_lstadd_back(&(p->lights), ft_lstnew(nl));
	return (true);
}
