#ifndef COLOR_H
# define COLOR_H

uint32_t	get_rgba(int r, int g, int b, int a);
uint32_t	get_rgba_from_tcol(t_color col);
t_color		color_new(double r, double g, double b);
t_color		color_scale(t_color col, double scale);
t_color		color_add(t_color col1, t_color col2);
t_color	get_ambient_color(t_scene *sc, t_hitrec *hit);
t_color	get_background_color(t_ray *ray);
void	color_clamp(t_color *color);

#endif
