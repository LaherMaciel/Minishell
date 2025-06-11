/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:15:26 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/11 18:31:13 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_strtoll(const char *str, char **endptr, int base)
{
	const char	*ptr;
	long long	result;
	int			digit;
	int			sign;

	result = 0;
	sign = 1;
	ptr = str;
	if (base != 10)
		return (0);
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr == '-')
	{
		sign = -1;
		ptr++;
	}
	else if (*ptr == '+')
		ptr++;
	while (ft_isdigit(*ptr))
	{
		digit = *ptr - '0';
		if (sign == 1 && (result > LLONG_MAX / 10
				|| (result == LLONG_MAX / 10 && digit > LLONG_MAX % 10)))
		{
			errno = ERANGE;
			if (endptr)
				*endptr = (char *)ptr;
			return (LLONG_MAX);
		}
		else if (sign == -1 && (result > -(LLONG_MIN / 10)
				|| (result == -(LLONG_MIN / 10) && digit > -(LLONG_MIN % 10))))
		{
			errno = ERANGE;
			if (endptr)
				*endptr = (char *)ptr;
			return (LLONG_MIN);
		}
		result = result * 10 + digit;
		ptr++;
	}
	if (endptr)
		*endptr = (char *)ptr;
	return (result * sign);
}
