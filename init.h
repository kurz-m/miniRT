#ifndef INIT_H
# define INIT_H

/// @brief Function for initializing the different parameters
/// of the t_cam struct. init_cam calculates the unit vector
/// for the viewport in horizontal and vertical direction.
/// Furthermore, it initializes the left uppermost pixel of
/// the viewport.
/// @param cam Struct holding the camera settings
void	init_cam(t_cam *cam);

// init_viewport input &t_cam
// init_pixel_ul
#endif
