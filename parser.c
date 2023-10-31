#include "miniRT.h"
#include "libft/include/libft.h"



double ft_strtod(char *s)
{
	double	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	while (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	if (*s != '.')
		return sign * num;
	s++;
	i = 1;
	while (*s && ft_isdigit(*s))
	{
		num += pow(10, -i) * (*s - '0');
		s++;
		i++;
	}
	return sign * num;
}
