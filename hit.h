/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:19:01 by flauer            #+#    #+#             */
/*   Updated: 2023/11/27 16:19:01 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

/// @brief Main entry point for calculating intersections between
/// objects and the ray
/// @param scene Main struct holding all the elements
/// @param ray Ray being shot into the scene
/// @param hitrec Structure holding the hit record of the ray
/// @return true if new hit was found, false if not
bool	hit_objects(t_scene *scene, t_ray *ray, t_hitrec *hitrec);

/// @brief Function for calculating intersections with a sphere
/// @param sp The sphere object
/// @param ray Ray being shot into the scene
/// @param norm const reference to the surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_sphere(t_obj *obj, t_ray *ray, t_vec3d *const norm);

/// @brief Function for calculating intersections with a plane
/// @param pl The plane object
/// @param ray Ray being shot into the scene
/// @param norm const reference to the surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_plane(t_obj *obj, t_ray *ray, t_vec3d *const norm);

/// @brief Function for calculating intersections with a cylinder
/// @param sp The cylinder object
/// @param ray Ray being shot into the scene
/// @param norm const reference to the surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_cylinder(t_obj *obj, t_ray *ray, t_vec3d *const norm);

/// @brief Function for calculating intersections with a cone
/// @param sp The cone object
/// @param ray Ray being shot into the scene
/// @param norm const reference to the surface norm vector
/// @return -1.0 if no hit was found, otherwise the scalar for intersection
double	hit_cone(t_obj *obj, t_ray *ray, t_vec3d *const norm);

#endif
