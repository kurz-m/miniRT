#include <fcntl.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "parse.h"
#include "utils.h"

/**
 * @brief Utility function to parse a single line given
 * by the get_next_line function.
 * 
 * @param p Struct containing the heads of the linked obj lists.
 * @param line The string read from get_next_line.
 * @return true If the parsing was successful.
 * @return false If the parsing contained an error.
 */
static bool	parse_line(t_parse *p, const char *line)
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
	else if (args && ft_strncmp(args[0], "co", 3) == 0)
		ret = parse_cone(p, args);
	else if (args && ft_strncmp(args[0], "#", 1) != 0)
		return (ft_error(args[0], "bad object specifier", NULL),
			free_arr(args), false);
	free_arr(args);
	return (ret);
}

/**
 * @brief Utility function to copy the light objects from the linked list
 * into an array for optimized computing.
 * @param scene Struct containing the current scene.
 * @param parse Struct containing the parsed `.rt` file.
 */
static void	copy_lights(t_scene *const scene, const t_parse *parse)
{
	t_list	*light;
	t_obj	*content;
	int		i;

	i = 0;
	light = parse->lights;
	while (light)
	{
		content = (t_obj *)light->content;
		scene->lights[i++] = (t_obj){
			.type = content->type,
			.color = content->color,
			.pos = content->pos,
			.light.brightness = content->light.brightness,
		};
		light = light->next;
	}
}

/**
 * @brief Utility function to cleanup the parser. The flag specifies
 * if, after a fail, the scene also needs to be cleaned up.
 * 
 * @param scene Struct containing the scene properties.
 * @param parser Struct containing the parsed objects.
 * @param flag Specifying what memory needs to be cleaned.
 * @return false Hand down false to return it from the main parser.
 */
static bool	cleanup_parser(t_scene *scene, t_parse *parser, char flag)
{
	if (flag == 'B')
	{
		free(scene->lights);
		free(scene->objs);
	}
	ft_lstclear(&parser->lights, &free);
	ft_lstclear(&parser->objects, &free);
	return (false);
}

/**
 * @brief Utility function to copy the objects from the linked list
 * into the array of structs in the main scene struct. The function
 * allocates memory for the lights and objects array. This array
 * needs to be free'd from the calling function.
 * 
 * @param scene Main structure holding all the objects and scene attributes
 * @param parse Struct holding the parsed objects
 * @return true If copying was successful.
 * @return false If copying failed.
 */
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
	cleanup_parser(scene, parse, 'L');
	return (true);
}

bool	parse(t_scene *scene, const char *filepath)
{
	int		fd;
	t_parse	parse;
	char	*tmp_line;
	char	*line;

	if (ft_strncmp(filepath + ft_strlen(filepath) - 3, ".rt", 3))
		return (ft_error(BAD_EXT, NULL, NULL));
	parse = (t_parse){};
	*scene = (t_scene){};
	fd = open(filepath, O_RDONLY);
	tmp_line = get_next_line(fd);
	while (tmp_line)
	{
		line = ft_strtrim(tmp_line, "\n");
		free(tmp_line);
		if (!parse_line(&parse, line))
			return (free(line), cleanup_parser(scene, &parse, 'L'));
		free(line);
		tmp_line = get_next_line(fd);
	}
	if (init_obj(scene, &parse) == false)
	{
		return (cleanup_parser(scene, &parse, 'B'));
	}
	return (true);
}
