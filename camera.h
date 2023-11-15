#ifndef CAMERA_H
# define CAMERA_H

int		get_focal_length(uint8_t fov);
t_vec3d	get_pixel_center(t_cam *cam, int i, int j);
t_vec3d	get_pixel_random(t_cam *cam, int i, int j);

#endif
