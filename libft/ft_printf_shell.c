/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:08:21 by lualbuqu          #+#    #+#             */
/*   Updated: 2025/01/22 13:55:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printargs_shell(char **s);
char	*ft_printargsn_shell(char **s);
char	*ft_printargsc_shell(char **s);
char	*ft_printargscn_shell(char **s);

char	*ft_format_shell(va_list args, const char variable)
{
	if (variable == 'c')
		return (ft_putchar_shell(va_arg(args, int)));
	else if (variable == 's')
		return (ft_putstr_shell(va_arg(args, char *)));
	else if (variable == 'a')
		return (ft_printargs_shell(va_arg(args, char **)));
	else if (variable == 'A')
		return (ft_printargsc_shell(va_arg(args, char **)));
	else if (variable == 't')
		return (ft_printargsn_shell(va_arg(args, char **)));
	else if (variable == 'T')
		return (ft_printargscn_shell(va_arg(args, char **)));
	else if (variable == 'd' || variable == 'i')
		return (ft_putnbr_shell(va_arg(args, int), NULL));
	else if (variable == 'u')
		return (ft_putnbr_u_shell(va_arg(args, unsigned int), NULL));
	else if (variable == 'x' || variable == 'X')
		return (ft_puthex_shell(va_arg(args, unsigned int), variable, NULL));
	else if (variable == 'p')
		return (ft_putptr_shell(va_arg(args, unsigned long), NULL));
	else if (variable == '%')
		return (ft_putchar_shell('%'));
	return (0);
}

int	ft_printf_shell(const char *str, ...)
{
	int		i;
	char	*result;
	va_list	args;

	if (!str)
		return (-1);
	i = 0;
	result = NULL;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			result = ft_strjoin2(result, ft_format_shell(args, str[i + 1]), 3);
			i++;
		}
		else
			result = ft_strjoin2(result, ft_putchar_shell(str[i]), 3);
		i++;
	}
	i = write(1, result, ft_strlen(result));
	free(result);
	va_end(args);
	return (i);
}
