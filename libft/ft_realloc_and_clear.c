/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_and_clear.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:48:11 by marvin            #+#    #+#             */
/*   Updated: 2025/07/21 14:48:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc_and_clear(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!new_size)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}
