#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../vec3d.h"

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
