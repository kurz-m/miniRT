/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:44 by flauer            #+#    #+#             */
/*   Updated: 2023/11/27 16:17:45 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

bool	ft_error(char *m1, char *m2, char *m3)
{
	if (m2 == NULL && m3 == NULL)
		ft_fprintf(2, "miniRT: error: %s\n", m1);
	else if (m3 == NULL)
		ft_fprintf(2, "miniRT: %s: %s\n", m1, m2);
	else
		ft_fprintf(2, "miniRT: %s: %s: %s\n", m1, m2, m3);
	return (false);
}

bool	ft_error2(char *m1, char *m2, char *m3, void *to_free)
{
	free(to_free);
	if (m2 == NULL && m3 == NULL)
		ft_fprintf(2, "miniRT: error: %s\n", m1);
	else if (m3 == NULL)
		ft_fprintf(2, "miniRT: %s: %s\n", m1, m2);
	else
		ft_fprintf(2, "miniRT: %s: %s: %s\n", m1, m2, m3);
	return (false);
}

bool	ft_error3(char **arr, char *m1)
{
	int	i;

	i = 0;
	ft_fprintf(2, "minirt:");
	while (arr && arr[i])
	{
		ft_fprintf(2, " %s", arr[i]);
		i++;
	}
	ft_fprintf(2, ": %s\n", m1);
	return (false);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
