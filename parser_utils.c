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
	if (!parse_double(&vec->x, args[0], -1, 1)
		|| !parse_double(&vec->y, args[1], -1, 1)
		|| !parse_double(&vec->z, args[2], -1, 1))
		return (free_arr(args), false);
	*vec = vec_norm(*vec);
	free_arr(args);
	return (true);
}

bool	parse_color(t_color *col, char *str)
{
	char	**args;
	int		r;
	int		g;
	int		b;

	args = ft_split(str, ',');
	if (!args || ft_arrlen(args) != 3)
		return (free_arr(args), false);
	if (!parse_int(&r, args[0], 0, 255)
		|| !parse_int(&g, args[1], 0, 255)
		|| !parse_int(&b, args[2], 0, 255))
		return (free_arr(args), false);
	col->r = (double)r / 255.;
	col->g = (double)g / 255.;
	col->b = (double)b / 255.;
	free_arr(args);
	return (true);
}

bool	parse_int(int *val, char *s, int lower, int upper)
{
	int			i;
	long long	num;

	i = 0;
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

bool	parse_double(double *val, char *s, double lower, double upper)
{
	int		i;
	bool	point;

	i = 0;
	point = false;
	if (s && s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s && s[i])
	{
		if (s[i] == '.' && !point)
			point = true;
		else if ((s[i] == '.' && point) || !ft_isdigit(s[i]))
			return (ft_error(s, BAD_DOUBLE, NULL));
		i++;
	}
	*val = ft_strtod(s);
	if (*val > upper || *val < lower)
		return (ft_error(s, "double value out of bounds!", NULL));
	return (true);
}
