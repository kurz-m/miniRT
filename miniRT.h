#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "structs.h"
# include <limits.h>

# define MULT_AMB "multiple definition of ambient lights!"
# define BAD_AMB "bad definition of ambient lights!"
# define MULT_CAM "multiple definitions of camera!"
# define BAD_CAM "bad definition of camera!"
# define BAD_FOV "bad field of view angle"
# define MALLOC_ERR "malloc error!"
# define BAD_LAMP "bad definition of light source!"
# define BAD_DOUBLE "bad double value!"
# define BAD_VEC "bad vector!"
# define BAD_COL "bad color!"
# define BAD_SP "bad sphere definition!"
# define BAD_PL "bad plane definition!"
# define BAD_CY "bad cylinder definition!"
# define BAD_INT "bad integer value!"
# define VAL_OUB "value out of bounds!"

double	ft_strtod(const char *s);
bool	ft_error(char *m1, char *m2, char *m3);
bool	ft_error2(char *m1, char *m2, char *m3, void *tofree);
bool	ft_error3(char **arr, char *m1);
int		ft_arrlen(char **arr);
void	free_arr(char **arr);
bool	parse_double(double *val, char *s, double lower, double upper);

bool	parse(t_scene *scene, char *fn);
bool	parse_vec(t_vec3d *vec, char *str);
bool	parse_norm_vec(t_vec3d *vec, char *str);
bool	parse_ambient(t_scene *scene, char **args);
bool	parse_cam(t_scene *scene, char **args);
bool	parse_lights(t_scene *scene, char **args);
bool	parse_sphere(t_scene *scene, char **args);
bool	parse_plane(t_scene *scene, char **args);
bool	parse_cylinder(t_scene *scene, char **args);
bool	parse_color(t_color *col, char *str);
bool	parse_int(int *val, char *s, int lower, int upper);

#endif
