#include "libft.h"
#include "miniRT.h"

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
	if (vec_len(*vec) != 1)
		return (free_arr(args), false);
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
	col->r = (uint8_t)r;
	col->g = (uint8_t)g;
	col->b = (uint8_t)b;
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

static bool	parse_line(t_scene *scene, char *line)
{
	char	**args;
	bool	ret;

	if (line && ft_strlen(line) == 0)
		return (true);
	args = ft_split(line, ' ');
	if (args && ft_strncmp(args[0], "A", 2) == 0)
		ret = parse_ambient(scene, args);
	else if (args && ft_strncmp(args[0], "C", 2) == 0)
		ret = parse_cam(scene, args);
	else if (args && ft_strncmp(args[0], "L", 2) == 0)
		ret = parse_lights(scene, args);
	else if (args && ft_strncmp(args[0], "sp", 3) == 0)
		ret = parse_sphere(scene, args);
	else if (args && ft_strncmp(args[0], "pl", 3) == 0)
		ret = parse_plane(scene, args);
	else if (args && ft_strncmp(args[0], "cy", 3) == 0)
		ret = parse_cylinder(scene, args);
	else if (args)
		return (ft_error(args[0], "bad object specifier", NULL),
			free_arr(args), false);
	else
		return (ft_error("fatal", NULL, NULL));
	free_arr(args);
	return (ret);
}

bool	parse(t_scene *scene, char *filepath)
{
	int		fd;
	char	*tmp_line;
	char	*line;

	fd = open(filepath, O_RDONLY);
	tmp_line = get_next_line(fd);
	while (tmp_line)
	{
		line = ft_strtrim(tmp_line, "\n");
		free(tmp_line);
		if (!parse_line(scene, line))
			return (false);
		free(line);
		tmp_line = get_next_line(fd);
	}
	return (true);
}
