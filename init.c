#include "MLX42.h"
#include "libft.h"
#include "defines.h"
#include "structs.h"
#include "vec3d.h"
#include "init.h"

static t_vec3d	calc_pixel_ul(t_cam *cam, t_vec3d cam_vec)
{
	t_vec3d		corner;

	corner = vec_scale(cam->delta_u, -0.5);
	corner = vec_add(corner, vec_scale(cam->delta_v, -0.5));
	corner = vec_add(corner, cam_vec);
	corner = vec_sub(corner, cam->pov);
	return (corner);
}

bool	init_mlx(mlx_t **mlx, mlx_image_t **image)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (mlx == NULL)
	{
		ft_fprintf(2, mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	*image = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (image == NULL)
	{
		mlx_close_window(*mlx);
		ft_fprintf(2, mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(*mlx, *image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		ft_fprintf(2, mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	init_cam(t_cam *cam)
{
	t_vec3d		cam_vec;
	t_vec3d		tmp_vec;

	tmp_vec = vec_new(1, 0, 0);
	cam_vec = vec_scale(cam->dir, cam->foc);
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
