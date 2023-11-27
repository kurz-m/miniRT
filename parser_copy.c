#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "parse.h"
#include "utils.h"
#include "hit.h"

void	copy_lights(t_scene *const scene, const t_parse *parse)
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
 * @brief Utility function to copy a sphere object from the linked list
 * into an array of objects for optimized computing.
 * @param scene Struct containing the current scene.
 * @param obj The current object from the parsed linked list.
 * @param i The position of the current object in the object array.
 */
static void	copy_sphere(t_scene *const scene, const t_obj *obj, const int i)
{
	scene->objs[i] = (t_obj){
		.type = obj->type,
		.color = obj->color,
		.pos = obj->pos,
		.hit = &hit_sphere,
		.sp.diameter = obj->sp.diameter,
		.s = obj->s,
	};
}

/**
 * @brief Utility function to copy a cylinder object from the linked list
 * into an array of objects for optimized computing.
 * @param scene Struct containing the current scene.
 * @param obj The current object from the parsed linked list.
 * @param i The position of the current object in the object array.
 */
static void	copy_cylinder(t_scene *const scene, const t_obj *obj, const int i)
{
	scene->objs[i] = (t_obj){
		.type = obj->type,
		.color = obj->color,
		.pos = obj->pos,
		.hit = &hit_cylinder,
		.cy.dir = obj->cy.dir,
		.cy.diam = obj->cy.diam,
		.cy.height = obj->cy.height,
		.s = obj->s,
	};
}

/**
 * @brief Utility function to copy a plane object from the linked list
 * into an array of objects for optimized computing.
 * @param scene Struct containing the current scene.
 * @param obj The current object from the parsed linked list.
 * @param i The position of the current object in the object array.
 */
static void	copy_plane(t_scene *const scene, const t_obj *obj, const int i)
{
	scene->objs[i] = (t_obj){
		.type = obj->type,
		.color = obj->color,
		.pos = obj->pos,
		.hit = &hit_plane,
		.pl.dir = obj->pl.dir,
		.s = obj->s,
	};
}

void	copy_objs(t_scene *const scene, const t_parse *parse)
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
