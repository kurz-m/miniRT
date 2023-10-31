#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "structs.h"
# include "libft.h"

# define MULT_AMB "multiple definition of ambient lights!"
# define BAD_AMB "bad definition of ambient lights!"
# define MULT_CAM "multiple definitions of camera!"
# define BAD_CAM "bad definition of camera!"
# define BAD_CAM_POV "bad camera orientation"
# define BAD_CAM_DIR "bad camera direction"
# define BAD_FOV "bad field of view angle"
# define MALLOC_ERR "malloc error!"
# define BAD_LAMP "bad definition of light source!"
# define BAD_L_POS "bad light position vector!"
# define BAD_L_BR "bad light brightness value!"
# define BAD_DOUBLE "bad double value!"
# define BAD_COL "bad definition of color!"

double	ft_strtod(const char *s);
bool	ft_error(char *m1, char *m2, char *m3);
bool	ft_error2(char *m1, char *m2, char *m3, void *tofree);
bool	ft_error3(char **arr, char *m1);
int		ft_arrlen(char **arr);
void	free_arr(char **arr);
bool	parse_double(double *val, char *s, double lower, double upper);

bool	parse(t_scene *scene, char *fn);
bool	parse_vec(t_vec3d *vec, char *str);
bool	parse_ambient(t_scene *scene, char **args);
bool	parse_cam(t_scene *scene, char **args);
bool	parse_lights(t_scene *scene, char **args);
bool	parse_sphere(t_scene *scene, char **args);
bool	parse_plane(t_scene *scene, char **args);
bool	parse_cylinder(t_scene *scene, char **args);
bool	parse_color(t_color *col, char *str);

#endif