/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:47:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/16 15:50:17 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief can be used to join and free the string
 *
 * @param s1 - string 1
 * @param s2 - string 2
 * @param flag - flag used to indicate witch string will be free. if flag = 1 it
 * frees s1, if flag = 2 frees s2 and if flag = 3 it frees s1 and s2
 * @return the_new_string
 */
char	*ft_strjoin3(char *s1, char s2, int flag)
{
	char	*sjoin;
	size_t	i;

	sjoin = ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (!sjoin)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			sjoin[i] = s1[i];
			i++;
		}
		if (flag == 1 || flag == 3)
			free(s1);
	}
	if (s2)
		sjoin[i] = s2;
	return (sjoin);
}
