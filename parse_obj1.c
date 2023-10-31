#include "miniRT.h"

bool	parse_ambiant(t_scene *scene, char **args)
{
	int	i;

	if (scene->amb.set)
		return (ft_error("ambiant lights already set!"));
	i = 0;
	
}