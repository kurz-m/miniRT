#include <math.h>
#include <stdint.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "camera.h"
#include "vec3d.h"

int	get_focal_length(uint8_t fov)
{
	double	fov_rad;

	fov_rad = (double)fov * M_PI / 180.0;
	return (round((double)WIDTH / 2.0) / tan(fov_rad / 2.0));
}

t_vec3d	get_pixel_center(t_cam *cam, int i, int j)
{
	t_vec3d	ret;

	ret = vec_add(vec_scale(cam->delta_u, i), vec_scale(cam->delta_v, j));
	ret = vec_add(cam->pixel_ul, ret);
	return (ret);
}
