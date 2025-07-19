/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:18:44 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/19 19:39:45 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char **a, char **b, int flag)
{
	char	*temp;

	temp = *a;
	if (flag)
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
