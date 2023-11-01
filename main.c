#include "libft.h"
#include "miniRT.h"

int	main(void)
{
	t_scene	scene;

	scene = (t_scene){};
	parse(&scene, "test.rt");
	return (0);
}
