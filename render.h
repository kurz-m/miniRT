#ifndef RENDER_H
# define RENDER_H

t_color	get_diffuse_light(t_color *obj_color, double angle, t_obj *obj);
static t_color	get_obj_lumination(t_scene *scene, t_hitrec *hitrec);
t_color	get_ray_color(t_scene *scene, t_ray *ray);
t_color	get_px_color(t_scene *scene, int i, int j);

#endif
