#ifndef UTILS_H
# define UTILS_H

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

bool	ft_error(char *m1, char *m2, char *m3);
bool	ft_error2(char *m1, char *m2, char *m3, void *to_free);
bool	ft_error3(char **arr, char *m1);

int		ft_arrlen(char **arr);
void	free_arr(char **arr);

#endif
