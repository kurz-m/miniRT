#include <math.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "colors.h"
#include "parse.h"
#include "utils.h"

bool	parse_vec(t_vec3d *vec, char *str)
{
	char	**args;

	args = ft_split(str, ',');
	if (!args || ft_arrlen(args) != 3)
		return (free_arr(args), false);
	if (!parse_double(&vec->x, args[0], -INFINITY, INFINITY)
		|| !parse_double(&vec->y, args[1], -INFINITY, INFINITY)
		|| !parse_double(&vec->z, args[2], -INFINITY, INFINITY))
		return (free_arr(args), false);
	free_arr(args);
	return (true);
}

bool	parse_norm_vec(t_vec3d *vec, char *str)
{
	char	**args;

	args = ft_split(str, ',');
	if (!args || ft_arrlen(args) != 3)
		return (free_arr(args), false);
	if (!parse_double(&vec->x, args[0], -INFINITY, INFINITY)
		|| !parse_double(&vec->y, args[1], -INFINITY, INFINITY)
		|| !parse_double(&vec->z, args[2], -INFINITY, INFINITY))
		return (free_arr(args), false);
	*vec = vec_norm(*vec);
	free_arr(args);
	return (true);
}

bool	parse_color(t_color *col, char *s_col, int *s, char *s_shiny)
{
	char	**args;
	int		r;
	int		g;
	int		b;

	args = ft_split(s_col, ',');
	if (!args || ft_arrlen(args) != 3)
		return (free_arr(args), ft_error("color", s_col, BAD_COL));
	if (!parse_int(&r, args[0], 0, 255)
		|| !parse_int(&g, args[1], 0, 255)
		|| !parse_int(&b, args[2], 0, 255))
		return (free_arr(args), ft_error("color", s_col, BAD_COL));
	col->r = (double)r / 255.;
	col->g = (double)g / 255.;
	col->b = (double)b / 255.;
	free_arr(args);
	if (s && !parse_int(s, s_shiny, 0, INT32_MAX))
		return (ft_error("shininess", s_shiny, BAD_SHNY));
	return (true);
}

bool	parse_int(int *val, char *s, int lower, int upper)
{
	int			i;
	long long	num;

	*val = 0;
	i = 0;
	if (!s)
		return (false);
	if (s && s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s && s[i])
	{
		if (!ft_isdigit(s[i]))
			return (ft_error(s, BAD_INT, NULL));
		i++;
	}
	num = ft_atoi(s);
	if (num < lower || num > upper)
		return (ft_error(s, VAL_OUB, NULL));
	*val = num;
	return (true);
}

t_parse_fcn	get_parse_fcn(char *id)
{
	static const char			*fcn_id[] = {"A", "C", "L", "sp", "pl",
		"cy", "co", NULL};
	static const t_parse_fcn	fcns[] = {&parse_ambient, &parse_cam,
		&parse_lights, &parse_sphere, &parse_plane, &parse_cylinder,
		&parse_cone, NULL};
	int							i;

	i = 0;
	while (fcn_id[i])
	{
		if (ft_strncmp(id, fcn_id[i], ft_strlen(fcn_id[i]) + 1) == 0)
			return (fcns[i]);
		++i;
	}
	return (NULL);
}
