#include "libft.h"
#include "structs.h"
#include "parse.h"
#include "error.h"
#include "miniRT.h"

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
		curr_obj = (t_obj *)obj->content;
		if (curr_obj->type == SPHERE)
			copy_sphere(scene, curr_obj, i);
		else if (curr_obj->type == CYLINDER)
			copy_cylinder(scene, curr_obj, i);
		else if (curr_obj->type == PLANE)
			copy_plane(scene, curr_obj, i);
		obj = obj->next;
		++i;
	}
}
