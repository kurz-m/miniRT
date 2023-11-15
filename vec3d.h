#ifndef VEC3D_H
# define VEC3D_H

# include <stdbool.h>


/// @brief Creates a new vector with the given values
/// @param x X value of the vector
/// @param y Y value of the vector
/// @param z Z value of the vector
/// @return New vector created on the stack
t_vec3d	vec_new(double x, double y, double z);

/// @brief Function for vector addition
/// @param v Vector v
/// @param w Vector w
/// @return New vector on the stack from addition of vector v and w
t_vec3d	vec_add(t_vec3d v, t_vec3d w);

/// @brief Function for vector addition
/// @param v Vector v
/// @param w Vector w
/// @return New vector on the stack from subtraction of vector w from v
t_vec3d	vec_sub(t_vec3d v, t_vec3d w);

/// @brief Scales vector v with the given scalar
/// @param v Vector v
/// @param scalar Scalar given as a double value
/// @return New vector which represents the scaled input vector
t_vec3d	vec_scale(t_vec3d v, double scalar);

/// @brief Calculation of the length of a vector
/// @param v Vector the length should be calculated from
/// @return Length of the vector as double
double	vec_len(t_vec3d v);

/// @brief Calculation of the dot product of 2 vectors
/// @param v Vector v
/// @param w Vector w
/// @return Dot product of the 2 vectors as double
double	vec_dot(t_vec3d v, t_vec3d w);

/// @brief Calculation of the cross product of 2 vectors
/// @param v Vector v
/// @param w Vector w
/// @return New vector as result from v X w
t_vec3d	vec_cross(t_vec3d v, t_vec3d w);

/// @brief Normalizes the given vector
/// @param v Vector v
/// @return New vector from normalizing the vector v
t_vec3d	vec_norm(t_vec3d v);

/// @brief Special case for returning the dot product of a
/// vector with itself
/// @param v Vector v
/// @return Squared length of the vector v as double
double	vec_sqr_len(t_vec3d v);

/// @brief Checks if 2 vectors are identical
/// @param v Vector v
/// @param w Vector w
/// @return true if vectors are equal, otherwise false
bool	vec_equal(t_vec3d v, t_vec3d w);

/// @brief Function for calculating the distance of 2 points
/// @param p First point
/// @param q Second point
/// @return Distance between point p and point q as double
double	vec_dist(t_point3d p, t_point3d q);

#endif
