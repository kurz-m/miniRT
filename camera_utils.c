#include <math.h>
#include "libft.h"
#include "structs.h"
#include "vec3d.h"
#include "miniRT.h"

int	get_focal_length(uint8_t fov)
{
	return (round((double)WIDTH / 2.0) / tan((double)fov / 2.0));
}

t_vec3d	get_pixel_center(t_cam *cam, int i, int j)
{
	t_vec3d	ret;

	ret = vec_add(vec_scale(cam->delta_u, i), vec_scale(cam->delta_v, j));
	ret = vec_add(cam->pixel_ul, ret);
	return (ret);
}
