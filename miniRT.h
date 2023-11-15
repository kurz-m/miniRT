#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>

# define WIDTH 1280
# define HEIGHT 720
# define T_MIN 1e-6
# define T_MAX 1000
# define AA_SAMPLES 10

int		ft_arrlen(char **arr);
void	free_arr(char **arr);

int		get_focal_length(uint8_t fov);
t_vec3d	get_pixel_center(t_cam *cam, int i, int j);
t_vec3d	get_pixel_random(t_cam *cam, int i, int j);

#endif
