#include "miniRT.h"

bool	ft_error(char *msg)
{
	ft_fprintf(2, "miniRT: error: %s\n", msg);
	return (false);
}