/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <laherwpayotmaciel@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:39:45 by lwencesl          #+#    #+#             */
/*   Updated: 2023/01/03 17:26:05 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fdprintf_shell(int fd, const char *format, ...)
{
	int		i;
	char	*result;
	va_list	args;

	if (!format)
		return (-1);
	i = 0;
	result = NULL;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			result = ft_strjoin2(result,
					ft_format_shell(args, format[i + 1]), 3);
			i++;
		}
		else
			result = ft_strjoin2(result, ft_putchar_shell(format[i]), 3);
		i++;
	}
	i = write(fd, result, ft_strlen(result));
	free(result);
	va_end(args);
	return (i);
}
