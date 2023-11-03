#include "libft.h"
#include "vec3d.h"
#include "miniRT.h"
#include <math.h>

int	get_focal_length(uint8_t fov)
{
	return (round((double)WIDTH / 2.0) / tan((double)fov / 2.0));
}
