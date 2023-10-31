#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../vec3d.h"
#include <math.h>

Test(vector_operation, vec_add_1)
{
	t_vec3d	v = {
		.x = 2,
		.y = 3,
		.z = 1,
	};
	t_vec3d	w = {
		.x = 1,
		.y = 3,
		.z = 0,
	};
	t_vec3d	res = vec_add(v, w);
	cr_assert(eq(flt, 3, res.x));
	cr_assert(eq(flt, 6, res.y));
	cr_assert(eq(flt, 1, res.z));
}

Test(vector_operation, vec_add_2)
{
	t_vec3d	v = {
		.x = -2,
		.y = 3,
		.z = -1,
	};
	t_vec3d	w = {
		.x = 1,
		.y = -3,
		.z = 0,
	};
	t_vec3d	res = vec_add(v, w);
	cr_assert(eq(flt, -1, res.x));
	cr_assert(eq(flt, 0, res.y));
	cr_assert(eq(flt, -1, res.z));
}

Test(vector_operation, vec_add_3)
{
	t_vec3d	v = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	w = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	res = vec_add(v, w);
	cr_assert(eq(flt, 0, res.x));
	cr_assert(eq(flt, 0, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_sub_1)
{
	t_vec3d	v = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	w = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	res = vec_add(v, w);
	cr_assert(eq(flt, 0, res.x));
	cr_assert(eq(flt, 0, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_sub_2)
{
	t_vec3d	v = {
		.x = -4,
		.y = 3,
		.z = 1,
	};
	t_vec3d	w = {
		.x = 2,
		.y = 0,
		.z = 1,
	};
	t_vec3d	res = vec_sub(v, w);
	cr_assert(eq(flt, -6, res.x));
	cr_assert(eq(flt, 3, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_sub_3)
{
	t_vec3d	v = {
		.x = 4.5,
		.y = 3,
		.z = 1.2,
	};
	t_vec3d	w = {
		.x = 2.4,
		.y = 0,
		.z = 1,
	};
	t_vec3d	res = vec_sub(v, w);
	cr_assert(eq(flt, 2.1, res.x));
	cr_assert(eq(flt, 3, res.y));
	cr_assert(eq(flt, 0.2, res.z));
}

Test(vector_operation, vec_dot_1)
{
	t_vec3d	v = {
		.x = 1,
		.y = 3,
		.z = -5,
	};
	t_vec3d	w = {
		.x = 4,
		.y = -2,
		.z = -1,
	};
	double	res = vec_dot(v, w);
	cr_assert(eq(flt, 3, res));
}

Test(vector_operation, vec_dot_2)
{
	t_vec3d	v = {
		.x = 0.4,
		.y = 5,
		.z = -1,
	};
	t_vec3d	w = {
		.x = 4,
		.y = -2,
		.z = -1,
	};
	double	res = vec_dot(v, w);
	cr_assert(eq(flt, -7.4, res));
}

Test(vector_operation, vec_dot_3)
{
	t_vec3d	v = {
		.x = 0.4,
		.y = 5,
		.z = -1.24,
	};
	t_vec3d	w = {
		.x = 4,
		.y = -0.24,
		.z = -1,
	};
	double	res = vec_dot(v, w);
	cr_assert(eq(flt, 1.64, res));
}

Test(vector_operation, vec_cross_1)
{
	t_vec3d	v = {
		.x = 1,
		.y = 2,
		.z = 3,
	};
	t_vec3d	w = {
		.x = 3,
		.y = 4,
		.z = 5,
	};
	t_vec3d	res = vec_cross(v, w);
	cr_assert(eq(flt, -2, res.x));
	cr_assert(eq(flt, 4, res.y));
	cr_assert(eq(flt, -2, res.z));
}

Test(vector_operation, vec_cross_2)
{
	t_vec3d	v = {
		.x = 1.4,
		.y = -2,
		.z = 3,
	};
	t_vec3d	w = {
		.x = 3,
		.y = 4,
		.z = -0.5,
	};
	t_vec3d	res = vec_cross(v, w);
	cr_assert(eq(flt, -11, res.x));
	cr_assert(eq(flt, 9.7, res.y));
	cr_assert(eq(flt, 11.6, res.z));
}

Test(vector_operation, vec_cross_3)
{
	t_vec3d	v = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	w = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	res = vec_cross(v, w);
	cr_assert(eq(flt, 0, res.x));
	cr_assert(eq(flt, 0, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_len_1)
{
	t_vec3d	v = {
		.x = 1,
		.y = 0,
		.z = 0,
	};
	double	res = vec_len(v);
	cr_assert(eq(flt, 1, res));
}

Test(vector_operation, vec_len_2)
{
	t_vec3d	v = {
		.x = 1,
		.y = 2,
		.z = 2,
	};
	double	res = vec_len(v);
	cr_assert(eq(flt, 3, res));
}

Test(vector_operation, vec_len_3)
{
	t_vec3d	v = {
		.x = 1,
		.y = 1,
		.z = 1,
	};
	double	res = vec_len(v);
	cr_assert(eq(flt, sqrtf(3), res));
}

Test(vector_operation, vec_scale_1)
{
	t_vec3d	v = {
		.x = 2.1,
		.y = 1.3,
		.z = -1,
	};
	t_vec3d	res = vec_scale(v, 2);
	cr_assert(eq(flt, 4.2, res.x));
	cr_assert(eq(flt, 2.6, res.y));
	cr_assert(eq(flt, -2, res.z));
}

Test(vector_operation, vec_scale_2)
{
	t_vec3d	v = {
		.x = 0.244,
		.y = 2,
		.z = 0,
	};
	t_vec3d	res = vec_scale(v, 0.5);
	cr_assert(eq(flt, 0.122, res.x));
	cr_assert(eq(flt, 1, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_scale_3)
{
	t_vec3d	v = {
		.x = 1,
		.y = 1.2,
		.z = 10,
	};
	t_vec3d	res = vec_scale(v, -1.5);
	cr_assert(eq(flt, -1.5, res.x));
	cr_assert(eq(flt, -1.8, res.y));
	cr_assert(eq(flt, -15, res.z));
}

Test(vector_operation, vec_norm_1)
{
	t_vec3d	v = {
		.x = 10,
		.y = 0,
		.z = 0,
	};
	t_vec3d	res = vec_norm(v);
	cr_assert(eq(flt, 1, res.x));
	cr_assert(eq(flt, 0, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_norm_2)
{
	t_vec3d	v = {
		.x = 0,
		.y = 2,
		.z = 0,
	};
	t_vec3d	res = vec_norm(v);
	cr_assert(eq(flt, 0, res.x));
	cr_assert(eq(flt, 1, res.y));
	cr_assert(eq(flt, 0, res.z));
}

Test(vector_operation, vec_norm_3)
{
	t_vec3d	v = {
		.x = 0,
		.y = 0,
		.z = 5,
	};
	t_vec3d	res = vec_norm(v);
	cr_assert(eq(flt, 0, res.x));
	cr_assert(eq(flt, 0, res.y));
	cr_assert(eq(flt, 1, res.z));
}

Test(vector_operation, vec_equal_1)
{
	t_vec3d	v = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_vec3d	w = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	bool	res = vec_equal(v, w);
	cr_assert(res == true);
}

Test(vector_operation, vec_equal_2)
{
	t_vec3d	v = {
		.x = 3,
		.y = 0,
		.z = 2,
	};
	t_vec3d	w = {
		.x = 4,
		.y = 0,
		.z = 3,
	};
	bool	res = vec_equal(v, w);
	cr_assert(res == false);
}

Test(vector_operation, vec_equal_3)
{
	t_vec3d	v = {
		.x = 1,
		.y = 0,
		.z = -20,
	};
	t_vec3d	w = {
		.x = 1,
		.y = 0,
		.z = -20,
	};
	bool	res = vec_equal(v, w);
	cr_assert(res == true);
}

Test(vector_operation, vec_dist_1)
{
	t_point3d	v = {
		.x = 3,
		.y = 2,
		.z = 1,
	};
	t_point3d	w = {
		.x = 5,
		.y = -1,
		.z = 2,
	};
	double	res = vec_dist(v, w);
	cr_assert(eq(flt, sqrtf(14), res));
}

Test(vector_operation, vec_dist_2)
{
	t_point3d	v = {
		.x = 0.25,
		.y = 2,
		.z = -1.2,
	};
	t_point3d	w = {
		.x = 5,
		.y = 0,
		.z = 1,
	};
	double	res = vec_dist(v, w);
	cr_assert(eq(flt, 5.60379, roundf(res * 100000) / 100000));
}

Test(vector_operation, vec_dist_3)
{
	t_point3d	v = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	t_point3d	w = {
		.x = 0,
		.y = 0,
		.z = 0,
	};
	double	res = vec_dist(v, w);
	cr_assert(eq(flt, 0, res));
}
