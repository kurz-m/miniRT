/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:16:57 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 18:24:29 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

/**
 * @brief Utility function to scale the current light of the object
 * with respect to the spot light and its diffuse component.
 * 
 * @param obj_color Color of the current object.
 * @param angle Hit angle of the light vector with respect to the obj norm.
 * @param obj The current light that is beeing checked.
 * @return t_color The scaled color.
 */
t_color	get_diffuse_light(
			const t_color *obj_color, const double angle, const t_obj *obj);

/**
 * @brief Main entry point for calculating how strong the object is
 * getting illuminated.
 * 
 * @param scene Struct containing the scene parameters.
 * @param hitrec Struct containing the parameters of the current
 * hit object.
 * @return t_color The scaled color.
 */
t_color	get_obj_lumination(t_scene *scene, t_hitrec *hitrec);

/**
 * @brief Function for getting the color of the current ray.
 * 
 * @param scene Struct containing the scene parameters.
 * @param ray Parameters of the current ray.
 * @return t_color Calculated color of the pixel in the viewport.
 */
t_color	get_ray_color(t_scene *scene, t_ray *ray);

/**
 * @brief Main entry point for calculating the color of the
 * current pixel of the viewport.
 * 
 * @param scene Struct containing the scene parameters.
 * @param i X-component of the currently rendered pixel.
 * @param j Y-component of the currently rendered pixel.
 * @return t_color Calculated color of the current pixel.
 */
t_color	get_px_color(t_scene *scene, int i, int j);

/**
 * @brief Utility to get the specular component of the light.
 * 
 * @param hitrec Struct containing parameters of currect hit object.
 * @param l Struct containing the light parameters.
 * @return t_color The scaled color.
 */
t_color	get_specular(const t_hitrec *hitrec, const t_lumi *l);

#endif
