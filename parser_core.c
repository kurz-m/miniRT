#include <fcntl.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "parse.h"
#include "utils.h"

static bool	parse_line(t_parse *p, char *line)
{
	char	**args;
	bool	ret;

	ret = true;
	if (line && ft_strlen(line) == 0)
		return (true);
	args = ft_split(line, ' ');
	if (args && ft_strncmp(args[0], "A", 2) == 0)
		ret = parse_ambient(p, args);
	else if (args && ft_strncmp(args[0], "C", 2) == 0)
		ret = parse_cam(p, args);
	else if (args && ft_strncmp(args[0], "L", 2) == 0)
		ret = parse_lights(p, args);
	else if (args && ft_strncmp(args[0], "sp", 3) == 0)
		ret = parse_sphere(p, args);
	else if (args && ft_strncmp(args[0], "pl", 3) == 0)
		ret = parse_plane(p, args);
	else if (args && ft_strncmp(args[0], "cy", 3) == 0)
		ret = parse_cylinder(p, args);
	else if (args && ft_strncmp(args[0], "#", 1) != 0)
		return (ft_error(args[0], "bad object specifier", NULL),
			free_arr(args), false);
	free_arr(args);
	return (ret);
}

static bool	init_obj(t_scene *scene, t_parse *parse)
{
	int		light_size;
	int		obj_size;

	*scene = (t_scene){
		.amb = parse->amb,
		.cam = parse->cam,
	};
	light_size = ft_lstsize(parse->lights);
	obj_size = ft_lstsize(parse->objects);
	scene->lights = ft_calloc(light_size + 1, sizeof(t_obj));
	scene->n_light = light_size;
	scene->objs = ft_calloc(obj_size + 1, sizeof(t_obj));
	scene->n_obj = obj_size;
	if (scene->lights == NULL || scene->objs == NULL)
		return (false);
	copy_objs(scene, parse);
	copy_lights(scene, parse);
	ft_lstclear(&(parse->lights), &free);
	ft_lstclear(&(parse->objects), &free);
	return (true);
}

static bool	cleanup_parser(t_scene *scene, t_parse *parser)
{
	free(scene->lights);
	free(scene->objs);
	ft_lstclear(&parser->lights, &free);
	ft_lstclear(&parser->objects, &free);
	return (false);
}

bool	parse(t_scene *scene, char *filepath)
{
	int		fd;
	t_parse	parse;
	char	*tmp_line;
	char	*line;

	parse = (t_parse){};
	*scene = (t_scene){};
	fd = open(filepath, O_RDONLY);
	tmp_line = get_next_line(fd);
	while (tmp_line)
	{
		line = ft_strtrim(tmp_line, "\n");
		free(tmp_line);
		if (!parse_line(&parse, line))
			return (false);
		free(line);
		tmp_line = get_next_line(fd);
	}
	if (init_obj(scene, &parse) == false)
	{
		return (cleanup_parser(scene, &parse));
	}
	return (true);
}
