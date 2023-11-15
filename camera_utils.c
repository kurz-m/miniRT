#include <math.h>
#include <stdint.h>
#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "camera.h"
#include "vec3d.h"

// static double random_double()
// {
// 	// Returns a random real in [0,1).
// 	return rand() / (RAND_MAX + 1.0);
// }

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

// t_vec3d	get_pixel_random(t_cam *cam, int i, int j)
// {
// 	t_vec3d	ret;
// 	double	ir;
// 	double	jr;

// 	ir = -0.5 + random_double() + i;
// 	jr = -0.5 + random_double() + j;
// 	ret = vec_add(vec_scale(cam->delta_u, ir), vec_scale(cam->delta_v, jr));
// 	ret = vec_add(cam->pixel_ul, ret);
// 	return (ret);
// }


// static void	move_cam(t_scene *sc, t_vec3d mov)
// {
// 	sc->cam.pov = vec_add(sc->cam.pov, mov);
// }

// static void	turn_cam(t_scene *sc, double horizontal, double vertical)
// {
// 	t_vec3d	new;

// 	if (horizontal)
// 		new = (t_vec3d){.x = horizontal};
// 	else if(vertical)
// 		new = (t_vec3d){.y = vertical};
// 	sc->cam.dir = vec_norm(vec_add(sc->cam.dir, new));
// }
