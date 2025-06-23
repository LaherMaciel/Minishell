/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_from_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:17:42 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/23 13:34:12 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_rm_from_array(char **array, size_t arraylen, size_t index)
{
	char	**new_array;
	size_t	i;
	size_t	j;

	if (!array)
		return (NULL);
	if (arraylen == 0)
		arraylen = ft_arraylen(array);
	new_array = ft_calloc(arraylen + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < arraylen)
	{
		if (i != index)
			new_array[j++] = array[i];
		i++;
	}
	if (array[index])
		free(array[index]);
	free(array);
	return (new_array);
}
