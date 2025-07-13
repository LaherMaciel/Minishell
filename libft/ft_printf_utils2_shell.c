/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lualbuqu <lualbuqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:05:43 by lualbuqu          #+#    #+#             */
/*   Updated: 2024/12/15 15:51:33 by lualbuqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_div_num_base_shell(long int number, int base)
{
	int	len;

	len = 0;
	if (number < 0)
	{
		number = -number;
		len++;
	}
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number = number / base;
		len++;
	}
	return (len);
}

char	*ft_puthex_shell(unsigned int number, char variable, char *result)
{
	if (number == 0)
		return (ft_putchar_shell('0'));
	if (number >= 16)
	{
		result = ft_strjoin2(result,
				ft_puthex_shell(number / 16, variable, result), 3);
		result = ft_strjoin2(result,
				ft_puthex_shell(number % 16, variable, result), 3);
	}
	else
	{
		if (number <= 9)
			result = ft_putchar_shell(number + '0');
		else
		{
			if (variable == 'x')
				result = ft_putchar_shell(number - 10 + 'a');
			else if (variable == 'X')
				result = ft_putchar_shell(number - 10 + 'A');
		}
	}
	return (result);
}

static char	*ft_ptr_shell(uintptr_t num, char *result)
{
	if (num >= 16)
	{
		result = ft_ptr_shell(num / 16, result);
		result = ft_strjoin2(result, ft_ptr_shell(num % 16, result), 3);
	}
	else
	{
		if (num <= 9)
			result = ft_putchar_shell(num + '0');
		else
			result = ft_putchar_shell(num - 10 + 'a');
	}
	return (result);
}

char	*ft_putptr_shell(unsigned long long ptr, char *result)
{
	if (ptr == 0)
		result = ft_putstr_shell("(nil)");
	else
	{
		result = ft_putstr_shell("0x");
		result = ft_strjoin2(result, ft_ptr_shell(ptr, result), 3);
	}
	return (result);
}
