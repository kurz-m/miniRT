#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "structs.h"

double	ft_strtod(const char *s);
bool	ft_error(char *msg);

bool	parse(t_scene *scene, char *fn);

#endif