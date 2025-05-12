/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:18:44 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/12 21:19:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char **a, char **b, int flag)
{
	char	*temp;

	temp = *a;
	if (flag == 1)
	{
		*a = ft_strdup(*b);
		free(*b);
		*b = ft_strdup(temp);
		free(temp);
	}
	else
	{
		*a = *b;
		*b = temp;
	}
}
