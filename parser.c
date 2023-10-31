#include "miniRT.h"

static bool	parse_line(t_scene *scene, char *line)
{
	char	**args;

	if (line && ft_strlen(line) == 0)
		return (true);
	args = ft_split(line, ' ');
	if (args && ft_strncmp(args[0], "A", 2))
		return (parse_ambiant(scene, args));
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
	ft_printf("miniRT: error: bad object specifier %s\n", args[0]);
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