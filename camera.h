/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:16:36 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 17:16:18 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

/// @brief Utility function to calculate the focal length 
/// from the given field of view.
/// @param fov Field of view in the range of 0 - 180
/// @return returns the focal length for the given scene.
int		get_focal_length(const uint8_t fov);

/// @brief Utility function to calculate the center of the
/// currently rendered pixel.
/// @param cam Struct that holds the camera properties.
/// @param i Y-component of the current pixel.
/// @param j X-component of the current pixel.
/// @return Vector pointing to the center of the current pixel.
t_vec3d	get_pixel_center(t_cam *cam, double i, double j);

// FIXME: Check if we still need this for anti-aliasing
t_vec3d	get_pixel_random(t_cam *cam, int i, int j);

#endif
