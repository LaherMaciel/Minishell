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

void	*ft_free_array(char **strstr, size_t len)
{
	size_t	i;

	i = 0;
	if (strstr)
	{
		if (len <= 0)
			len = ft_arraylen(strstr);
		while (i <= len)
			free(strstr[i++]);
		free(strstr);
	}
	return (NULL);
}
