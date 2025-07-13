/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lualbuqu <lualbuqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:09:02 by lualbuqu          #+#    #+#             */
/*   Updated: 2024/12/15 15:51:39 by lualbuqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putchar_shell(int c)
{
	char	*character;

	character = ft_calloc(sizeof(char), 2);
	character[0] = c;
	return (character);
}

char	*ft_putstr_shell(char *str)
{
	unsigned int	len;
	char			*result;

	if (!str)
		return (ft_putstr_shell("(null)"));
	len = 0;
	result = NULL;
	while (str[len])
	{
		result = ft_strjoin2(result, ft_putchar_shell(str[len]), 3);
		len++;
	}
	return (result);
}

char	*ft_putnbr_shell(long long int number, char *result)
{
	if (number < 0)
	{
		result = ft_strjoin(result, "-");
		number = -number;
		result = ft_strjoin(result, ft_putnbr_shell(number, result));
	}
	else if (number > 9)
	{
		result = ft_strjoin2(result, ft_putnbr_shell(number / 10, result), 3);
		result = ft_strjoin2(result, ft_putnbr_shell(number % 10, result), 3);
	}
	else
		result = ft_putchar_shell(number + '0');
	return (result);
}

char	*ft_putnbr_u_shell(unsigned long long int number, char *result)
{
	if (number > 9)
	{
		result = ft_strjoin2(result, ft_putnbr_shell(number / 10, result), 3);
		result = ft_strjoin2(result, ft_putnbr_shell(number % 10, result), 3);
	}
	else
		result = ft_putchar_shell('0');
	return (result);
}
