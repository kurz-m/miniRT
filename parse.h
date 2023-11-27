#ifndef PARSE_H
# define PARSE_H

/**
 * @brief Main entry point for parsing the p given by the .rt file
 * 
 * @param scene Main structure holding all the objects and scene attributes
 * @param fn Filename of the .rt file
 * @return true If the parsing of the p was successful
 * @return false If the parsing of the p was unsuccessful
 */
bool	parse(t_scene *scene, const char *fn);

/**
 * @brief Parses a vector from a given string in the form a,b,c
 * 
 * @param vec Address of a vector
 * @param str String the vector is being parsed from
 * @return true If the parsing of the vector was successful
 * @return false If the parsing of the vector was unsuccessful
 */
bool	parse_vec(t_vec3d *vec, char *str);

/**
 * @brief Parses a norm vector from a given string in the form a,b,c
 * 
 * @param vec Address of a norm vector
 * @param str String the norm vector is being parsed from
 * @return true If the parsing of the norm vector was successful
 * @return false If the parsing of the norm vector was unsuccessful
 */
bool	parse_norm_vec(t_vec3d *vec, char *str);

/**
 * @brief Parses the ambient light of the p from an array of strings
 * 
 * @param p Main structure holding all the objects and p attributes
 * @param args Array of strings holding the settings for the ambient light
 * @return true If the parsing of the ambient light was successful
 * @return false If the parsing of the ambient light was unsuccessful
 */
bool	parse_ambient(t_parse *p, char **args);

/**
 * @brief Parses the camera of the p from an array of strings
 * 
 * @param p Main structure holding all the objects and p attributes
 * @param args Array of strings holding the settings for the ambient light
 * @return true If the parsing of the camera was successful
 * @return false If the parsing of the camera was unsuccessful
 */
bool	parse_cam(t_parse *p, char **args);

/**
 * @brief Parses the lights of the p from an array of strings
 * 
 * @param p Main structure holding all the objects and p attributes
 * @param args Array of strings holding the settings for the ambient light
 * @return true If the parsing of the lights was successful
 * @return false If the parsing of the lights was unsuccessful
 */
bool	parse_lights(t_parse *p, char **args);

/**
 * @brief Parses the sphere object of the p from an array of strings
 * 
 * @param p Main structure holding all the objects and p attributes
 * @param args Array of strings holding the settings for the ambient light
 * @return true If the parsing of the sphere was successful
 * @return false If the parsing of the sphere was unsuccessful
 */
bool	parse_sphere(t_parse *p, char **args);

/**
 * @brief Parses the plane object of the p from an array of strings
 * 
 * @param p Main structure holding all the objects and p attributes
 * @param args Array of strings holding the settings for the ambient light
 * @return true If the parsing of the plane was successful
 * @return false If the parsing of the plane was unsuccessful
 */
bool	parse_plane(t_parse *p, char **args);

/**
 * @brief Parses the cylinder object of the p from an array of strings
 * 
 * @param p Main structure holding all the objects and p attributes
 * @param args Array of strings holding the settings for the ambient light
 * @return true If the parsing of the cylinder was successful
 * @return false If the parsing of the cylinder was unsuccessful
 */
bool	parse_cylinder(t_parse *p, char **args);

/**
 * @brief Parses the color from a string in the form of r,g,b
 * 
 * @param col Color struct holding the 3 colors red, green, and blue
 * @param str String the color is being parsed from
 * @return true If the parsing of the color was successful
 * @return false If the parsing of the color was unsuccessful
 */
bool	parse_color(t_color *col, char *s_col, int *s, char *s_shiny);

/**
 * @brief Helper function for parsing integers
 * 
 * @param val Pointer to an integer
 * @param s String the integer is being parsed from
 * @param lower Lower boundary of the allowed value
 * @param upper Upper boundary of the allowed value
 * @return true If the parsing of the integer was successful
 * @return false If the parsing of the integer was unsuccessful
 */
bool	parse_int(int *val, char *s, int lower, int upper);

/**
 * @brief Helper function for parsing doubles
 * 
 * @param val Pointer to a double
 * @param s String the double is being parsed from
 * @param lower Lower boundary of the allowed value
 * @param upper Upper boundary of the allowed value
 * @return true If the parsing of the double was successful
 * @return false If the parsing of the double was unsuccessful
 */
bool	parse_double(double *val, char *s, double lower, double upper);

/**
 * @brief Utility function to copy the light objects from the linked list
 * into an array for optimized computing.
 * @param scene Struct containing the current scene.
 * @param parse Struct containing the parsed `.rt` file.
 */
void	copy_lights(t_scene *const scene, const t_parse *parse);

/**
 * @brief Main entry point for the copy functions. It loops through
 * the linked list which contains the parsed objects from the `.rt`
 * file and copies it into the array of objects into the scene struct.
 * @param scene Struct containing the current scene.
 * @param parse Struct containing the parsed `.rt` file.
 */
void	copy_objs(t_scene *scene, const t_parse *parse);

/**
 * @brief Utility function for parse_double to extract the integer and
 * fractional part from the given string.
 * @param s The string representing the double value.
 * @return `double` The parsed double.
 */
double	ft_strtod(const char *s);

#endif
