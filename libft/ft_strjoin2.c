/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:47:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/02 15:26:10 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy_s1(char *s1, char *sjoin, size_t *i)
{
	if (s1)
	{
		while (s1[*i] != '\0')
		{
			sjoin[*i] = s1[*i];
			*i += 1;
		}
	}
	return (sjoin);
}

/**
 * @brief can be used to join and free the string
 *
 * @param s1 - string 1
 * @param s2 - string 2
 * @param flag - flag used to indicate witch string will be free. if flag = 1 it
 * frees s1, if flag = 2 frees s2 and if flag = 3 it frees s1 and s2
 * @return the_new_string
 */
char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char	*sjoin;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (ft_strdup(""));
	sjoin = ft_calloc((ft_strlen(s1) + ft_strlen(s2)), sizeof(char) + 1);
	if (!sjoin)
		return (NULL);
	i = 0;
	if (s1)
	{
		sjoin = copy_s1(s1, sjoin, &i);
		if (flag == 1 || flag == 3)
			free(s1);
	}
	j = -1;
	if (s2)
	{
		while (s2[++j] != '\0')
			sjoin[i++] = s2[j];
		if (flag == 2 || flag == 3)
			free(s2);
	}
	return (sjoin);
}
