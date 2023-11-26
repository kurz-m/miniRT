#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "init.h"

/// @brief Utility function to calculate the upper left
/// pixel of the viewport of the current scene.
/// @param cam Struct holding all the camera properties.
/// @param cam_vec Norm camera vector scaled with the focal length.
/// @return Vector pointing to the upper left pixel.
static t_vec3d	calc_pixel_ul(const t_cam *cam, const t_vec3d cam_vec)
{
	t_vec3d		corner;

	corner = vec_scale(cam->delta_u, -0.5);
	corner = vec_add(corner, vec_scale(cam->delta_v, -0.5));
	corner = vec_add(corner, cam_vec);
	corner = vec_sub(corner, cam->pov);
	return (corner);
}

/// @brief Function for initializing the mlx window and image
/// @param mlx Pointer to the mlx instance.
/// @param image Pointer to the mlx image instance.
/// @return `True` on success, `False` on fail.
static bool	init_mlx(mlx_t **mlx, mlx_image_t **image)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (mlx == NULL)
	{
		ft_fprintf(2, mlx_strerror(mlx_errno));
		return (false);
	}
	*image = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (image == NULL)
	{
		mlx_close_window(*mlx);
		ft_fprintf(2, mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(*mlx, *image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		ft_fprintf(2, mlx_strerror(mlx_errno));
		return (false);
	}
	return (true);
}

/// @brief calculate the camera specs.
/// 1. use the cross product of a random vector in the xz plane to get a
/// perpendicular vector which is in the direction of v in the image. (=delta_v)
/// 2. use the cross product of the delta_v and the cam_dir to get delta_u
/// 3. scale both vectors to HEIGHT and WIDTH to get the full viewport size
/// vectors and use them to calculate the upper left pixel vector from the
/// camera origin.
/// 4. norm both delta_u and delta_v again to get it to pixel scale.
/// 5. use tmp_vec again as the vector from the upper left corner of the pixel
/// to the pixel center and add it to the pixel_ul vector to get the pixel 
/// center.
/// @param cam 
static void	init_cam(t_cam *cam)
{
	t_vec3d		cam_vec;
	t_vec3d		tmp_vec;

	tmp_vec = vec_new(1, 0, 0);
	cam_vec = vec_scale(cam->dir, cam->foc);
	if (vec_len(vec_cross(tmp_vec, cam_vec)) == 0)
		tmp_vec = vec_new(0, 0, 1);
	cam->delta_v = vec_norm(vec_cross(tmp_vec, cam_vec));
	cam->delta_v = vec_scale(cam->delta_v, HEIGHT);
	cam->delta_u = vec_norm(vec_cross(cam->dir, cam->delta_v));
	cam->delta_u = vec_scale(cam->delta_u, WIDTH);
	cam->pixel_ul = calc_pixel_ul(cam, cam_vec);
	cam->delta_v = vec_norm(cam->delta_v);
	cam->delta_u = vec_norm(cam->delta_u);
	tmp_vec = vec_scale(vec_add(cam->delta_u, cam->delta_v), 0.5);
	cam->pixel_ul = vec_add(tmp_vec, cam->pixel_ul);
}

bool	init_main(mlx_t **mlx, mlx_image_t **image, t_cam *cam)
{
	init_cam(cam);
	return (init_mlx(mlx, image));
}
