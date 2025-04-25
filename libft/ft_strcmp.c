/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:24:25 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/04/25 15:27:14 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares two strings up to a specified number of characters.
 *
 * This function compares the strings 'str1' and 'str2' until a null-terminator
 * is encountered in either string. It returns an integer value indicating the
 * comparison result:
 * - Returns a value less than 0 if 'str1' is lexicographically less than
 *   'str2'.
 * - Returns 0 if both strings are lexicographically equals.
 * - Returns a value greater than 0 if 'str1' is lexicographically greater than
 *   'str2'.
 *
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @return An integer indicating the comparison result.
 */
int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	a;

	a = 0;
	while (str1[a] || str2[a])
	{
		if (str1[a] != str2[a])
			return ((unsigned char)str1[a] - (unsigned char)str2[a]);
		a++;
	}
	return (0);
}
