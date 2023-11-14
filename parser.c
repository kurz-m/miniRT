#include "libft.h"
#include "structs.h"
#include "parse.h"
#include "error.h"
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

void	copy_lights(t_scene *scene, t_parse *parse)
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

void	copy_sphere(t_scene *scene, t_obj *obj, int i)
{
	scene->objs[i] = (t_obj){
		.type = obj->type,
		.color = obj->color,
		.pos = obj->pos,
		.sp.diameter = obj->sp.diameter,
	};
}

void	copy_cylinder(t_scene *scene, t_obj *obj, int i)
{
	scene->objs[i] = (t_obj){
		.type = obj->type,
		.color = obj->color,
		.pos = obj->pos,
		.cy.dir = obj->cy.dir,
		.cy.diam = obj->cy.diam,
		.cy.height = obj->cy.height,
	};
}

void	copy_plane(t_scene *scene, t_obj *obj, int i)
{
	scene->objs[i] = (t_obj){
		.type = obj->type,
		.color = obj->color,
		.pos = obj->pos,
		.pl.dir = obj->pl.dir,
	};
}

void	copy_objs(t_scene *scene, t_parse *parse)
{
	t_list	*obj;
	t_obj	*curr_obj;
	int		i;

	i = 0;
	obj = parse->objects;
	while (obj)
	{
		curr_obj = (t_obj* )obj->content;
		if (curr_obj->type == SPHERE)
			copy_sphere(scene, curr_obj, i) ;
		else if (curr_obj->type == CYLINDER)
			copy_cylinder(scene, curr_obj, i);
		else if (curr_obj->type == PLANE)
			copy_plane(scene, curr_obj, i);
		obj = obj->next;
		++i;
	}
}

bool	init_obj(t_scene *scene, t_parse *parse)
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

bool	parse(t_scene *scene, char *filepath)
{
	int		fd;
	t_parse	parse;
	char	*tmp_line;
	char	*line;

	parse = (t_parse){};
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
		free(scene->lights);
		free(scene->objs);
		ft_lstclear(&parse.lights, &free);
		ft_lstclear(&parse.objects, &free);
		return (false);
	}
	return (true);
}
