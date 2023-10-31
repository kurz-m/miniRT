#include "miniRT.h"

bool	parse_vec(t_vec3d *vec, char *str)
{
	char	**args;

	args = ft_split(str, ",");
	if (!args || ft_arrlen(args) != 3)
		return (false);
	
	return (true);
}

bool	parse_double(double *val, char *s, double lower, double upper)
{
	int		i;
	bool	point;

	i = 0;
	point = false;
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

	if (line && ft_strlen(line) == 0)
		return (true);
	args = ft_split(line, ' ');
	if (args && ft_strncmp(args[0], "A", 2))
		return (parse_ambient(scene, args));
	else if (args && ft_strncmp(args[0], "C", 2))
		return (parse_cam(scene, args));
	else if (args && ft_strncmp(args[0], "L", 2))
		return (parse_lights(scene, args));
	else if (args && ft_strncmp(args[0], "sp", 3))
		return (parse_sphere(scene, args));
	else if (args && ft_strncmp(args[0], "pl", 3))
		return (parse_plane(scene, args));
	else if (args && ft_strncmp(args[0], "cy", 3))
		return (parse_cylinder(scene, args));
	else if (args)
		return (ft_error(args[0], "bad object specifier", NULL));
	return (false);
}

bool	parse(t_scene *scene, char *filepath)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(scene, line))
			return (false);
		line = get_next_line(fd);
	}
	return (true);
}