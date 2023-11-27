/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:16:16 by makurz            #+#    #+#             */
/*   Updated: 2023/11/27 16:16:18 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

/// @brief Creates a new vector with the given values
/// @param x X value of the vector
/// @param y Y value of the vector
/// @param z Z value of the vector
/// @return New vector created on the stack
t_vec3d	vec_new(const double x, const double y, const double z);

/// @brief Function for vector addition
/// @param v Vector v
/// @param w Vector w
/// @return New vector on the stack from addition of vector v and w
t_vec3d	vec_add(const t_vec3d v, const t_vec3d w);

/// @brief Function for vector addition
/// @param v Vector v
/// @param w Vector w
/// @return New vector on the stack from subtraction of vector w from v
t_vec3d	vec_sub(const t_vec3d v, const t_vec3d w);

/// @brief Scales vector v with the given scalar
/// @param v Vector v
/// @param scalar Scalar given as a double value
/// @return New vector which represents the scaled input vector
t_vec3d	vec_scale(const t_vec3d v, const double scalar);

/// @brief Calculation of the length of a vector
/// @param v Vector the length should be calculated from
/// @return Length of the vector as double
double	vec_len(const t_vec3d v);

/// @brief Calculation of the dot product of 2 vectors
/// @param v Vector v
/// @param w Vector w
/// @return Dot product of the 2 vectors as double
double	vec_dot(const t_vec3d v, const t_vec3d w);

/// @brief Calculation of the cross product of 2 vectors
/// @param v Vector v
/// @param w Vector w
/// @return New vector as result from v X w
t_vec3d	vec_cross(const t_vec3d v, const t_vec3d w);

/// @brief Normalizes the given vector
/// @param v Vector v
/// @return New vector from normalizing the vector v
t_vec3d	vec_norm(const t_vec3d v);

/// @brief Special case for returning the dot product of a
/// vector with itself
/// @param v Vector v
/// @return Squared length of the vector v as double
double	vec_sqr_len(const t_vec3d v);

/// @brief Checks if 2 vectors are identical
/// @param v Vector v
/// @param w Vector w
/// @return true if vectors are equal, otherwise false
bool	vec_equal(const t_vec3d v, const t_vec3d w);

/// @brief Function for calculating the distance of 2 points
/// @param p First point
/// @param q Second point
/// @return Distance between point p and point q as double
double	vec_dist(const t_point3d p, const t_point3d q);

#endif
