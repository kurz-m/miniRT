#include <math.h>
#include "libft.h"

/**
 * @brief Utility function to get the integer part of the double.
 * 
 * @param str String the double is being parsed from
 * @return double The integer part of the double.
 */
static double	get_int_part(const char *s)
{
	double	num;
	int		i;

	num = 0;
	i = 0;
	while (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		num = (num * 10) + (s[i] - '0');
		i++;
	}
	return (num);
}

/**
 * @brief Utility function to get the fractional part of the double.
 * 
 * @param str String the double is being parsed from
 * @return double The updated num with the fractional part.
 */
static double	get_fract_part(const char *str)
{
	double	num;
	int		i;
	char	*s;

	s = (char *)str;
	num = 0;
	while (*s && (*s == '+' || *s == '-'))
		s++;
	while (*s && ft_isdigit(*s))
		s++;
	if (*s != '.')
		return (num);
	i = 1;
	while (s[i] && ft_isdigit(s[i]))
	{
		num += pow(10, -i) * (s[i] - '0');
		i++;
	}
	return (num);
}

double	ft_strtod(const char *s)
{
	double	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	num = get_int_part(s) * sign;
	if (sign < 0)
		num -= get_fract_part(s);
	else
		num += get_fract_part(s);
	return (num);
}
