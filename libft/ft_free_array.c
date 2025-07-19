/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:39:14 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/02/09 19:20:46 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_array(char **array, size_t len)
{
	size_t	i;

	i = 0;
	if (array)
	{
		if (len <= 0)
			len = ft_arraylen(array);
		while (i <= len)
			free(array[i++]);
		free(array);
	}
	return (NULL);
}
