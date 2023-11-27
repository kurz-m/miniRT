/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:16:39 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 16:16:39 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/// @brief Utility function to get rgba values for the color struct.
/// The color struct contains r,g, and b values ranging from 0 - 1.
/// This function converts them to a color range between 0 - 255.
/// @param col Color struct containing rgb.
/// @return Returns a uint32 where each component occupies 8 bits.
uint32_t	get_rgba_from_tcol(const t_color col);

/// @brief Returns a new color struct initialized with the given rgb values.
/// @param r Red value.
/// @param g Green value.
/// @param b Blue value.
/// @return Newly created color struct.
t_color		color_new(const double r, const double g, const double b);

/// @brief Utility function to scale the color struct.
/// @param col Color struct containing rgb values.
/// @param scale Coefficient the color is scaled with.
/// @return Scaled color as a new color struct.
t_color		color_scale(const t_color col, const double scale);

/// @brief Utility function to add the rgb values of one color to another.
/// @param col1 Base color.
/// @param col2 Color that is being added.
/// @return The summed up color structure.
t_color		color_add(const t_color col1, const t_color col2);

/// @brief Utility function to light the scene according to the
/// given ambient color. The color of the object is multiplied
/// by the color of the ambient light and its ratio (0 - 1).
/// @param sc Struct containing the scene properties.
/// @param hit Struct containing the current hit object.
/// @return The color scaled with the ambient light ratio.
t_color		get_ambient_color(const t_scene *sc, const t_hitrec *hit);

/// @brief Utility function to get the background color if no object was hit.
/// @param ray Struct containing the current ray.
/// @return Returns a color struct containing the background color.
t_color		get_background_color(const t_ray *ray);

/// @brief Utility function to clamp the color within its borders.
/// The borders are 0 for the minimum and 1 for the maximum value.
/// @param color The color that needs to be clamped by reference.
void		color_clamp(t_color *color);

#endif
