#include "libft.h"
#include "vec3d.h"
#include "structs.h"
#include "miniRT.h"

static double	get_int_part(const char *s)
{
	double	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		num = (num * 10) + (s[i] - '0');
		i++;
	}
	return (sign * num);
}

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

	num = get_int_part(s);
	if (num < 0)
		num -= get_fract_part(s);
	else
		num += get_fract_part(s);
	return (num);
}
