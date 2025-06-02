/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <lwencesl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:38:25 by lwencesl          #+#    #+#             */
/*   Updated: 2023/06/20 16:10:59 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* 
char	*empty_src(void)
{
	char	*new_src;

	new_src = ft_calloc(2, sizeof(char));
	if (!new_src)
		return (NULL);
	return (new_src);
}
 */
/**
 * @brief Duplicates a string by creating a new dynamically allocated copy.
 *
 * This function creates a new string that is an exact copy of the input string
 * 's'. It allocates memory for the new string, copies the characters from 's'
 * into it, and adds a null-terminator at the end.
 *
 * @param s The input string to be duplicated.
 * @return A pointer to the newly allocated duplicated string, or NULL if memory
 * allocation fails.
 */
char	*ft_strdup(const char *src)
{
	char	*copy;
	size_t	i;

	if (!src)
		return (NULL);
	copy = ft_calloc((ft_strlen(src) + 1), sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	return (copy);
}
