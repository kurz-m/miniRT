#include "libft.h"

void	*resize_array(void *array, size_t current, size_t new, size_t type)
{
	void	*new_array;

	new_array = ft_calloc(new, type);
	if (new_array == NULL)
	{
		return (NULL);
	}
	if (array != NULL)
	{
		ft_memcpy(new_array, array, current * type);
		free(array);
	}
	return (new_array);
}
