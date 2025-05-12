/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:46 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/12 21:01:38 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief can be used to join and free the string
 *
 * @param s1 - string 1
 * @param s2 - string 2
 * @param flag - flag used to indicate witch string will be free. if flag = 1 it
 * frees s1, if flag = 2 frees s2 and if flag = 3 it frees s1 and s2
 * @return the_new_string
 */

/* 
char	**ft_append_to_array(char **array, char *str, int flag)
{
	char	**new_array;
	size_t	len;
	size_t	i;

	if (!array)
	{
		new_array = ft_calloc(2, sizeof(char *));
		if (!new_array)
			return (NULL);
		if (str != NULL)
			new_array[0] = ft_strdup(str);
		if (str && (flag == 2 || flag == 3))
			free(str);
		return (new_array);
	}
	len = ft_arraylen(array);
	new_array = ft_calloc(len + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (flag == 1 || flag == 3)
			new_array[i] = array[i];
		else
			new_array[i] = ft_strdup(array[i]);
		i++;
	}
	if (flag == 1 || flag == 3)
		free(array);
	if (str)
	{
		if (flag == 2 || flag == 3)
		{
			new_array[i] = ft_strdup(str);
			free(str);
		}
		else
			new_array[i] = str;
	}
	else
		return (new_array);
	if (!new_array[i])
	{
		if (flag == 1 || flag == 3)
			ft_free_array(new_array);
		else
			free(new_array);
		return (NULL);
	}
	return (new_array);
}
 */
char	**ft_append_to_array(char **array, size_t arraylen,
	char *str, int flag)
{
	char	**new_array;
	size_t	i;

	if (!array)
	{
		new_array = ft_calloc(2, sizeof(char *));
		if (!new_array)
			return (NULL);
		if (str)
		{
			if (flag == 2 || flag == 3)
			{
				new_array[0] = ft_strdup(str);
				free(str);
			}
			else
				new_array[0] = str;
		}
		return (new_array);
	}
	new_array = ft_calloc(arraylen + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (++i < arraylen)
		new_array[i] = array[i];
	if (str)
	{
		if (flag == 2 || flag == 3)
		{
			new_array[i] = ft_strdup(str);
			free(str);
			if (!new_array[i])
			{
				if (flag == 1 || flag == 3)
					ft_free_array(new_array, 0);
				else
					free(new_array);
				return (NULL);
			}
		}
		else
			new_array[i] = str;
	}
	if (flag == 1 || flag == 3)
		free(array);
	return (new_array);
}
