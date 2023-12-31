/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:16:54 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 16:16:54 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

/// @brief Creates a new ray with the given origin and the direction
/// @param origin Origin of the ray as t_point3d
/// @param dir Direction of the rays as t_vec3d
/// @return New ray
t_ray		ray_new(t_point3d origin, t_vec3d dir);

/// @brief Function for getting a point on a ray
/// @param ray Ray from where to calculate the point
/// @param t Real number to move point along the ray
/// @return Point on the rays as t_point3d
t_point3d	ray_at(const t_ray *ray, const double t);

#endif
