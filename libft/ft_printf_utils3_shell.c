/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3_minishell.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:18:18 by lawences          #+#    #+#             */
/*   Updated: 2025/03/24 14:18:18 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printargs_shell(char **s)
{
	size_t	cont;
	char	*result;

	if (!s)
		return (ft_putstr_shell("(null)"));
	cont = 0;
	if (s[cont])
		result = ft_strjoin2(NULL, ft_putstr_shell(s[cont]), 3);
	while (s[++cont])
	{
		result = ft_strjoin2(result, ft_putstr_shell(s[cont]), 3);
		result = ft_strjoin2(result, " ", 1);
	}
	return (result);
}

char	*ft_printargsn_shell(char **s)
{
	char	*result;
	size_t	cont;

	if (!s)
		return (ft_putstr_shell("(null)"));
	cont = 0;
	if (s[cont])
		result = ft_strjoin2(NULL, ft_putstr_shell(s[cont]), 3);
	while (s[++cont])
	{
		result = ft_strjoin2(result, ft_putstr_shell(s[cont]), 3);
		result = ft_strjoin2(result, "\n\n", 1);
	}
	return (result);
}

char	*ft_printargsc_shell(char **s)
{
	size_t	cont;
	char	*result;

	if (!s)
		return (ft_putstr_shell("(null)"));
	cont = -1;
	result = ft_strjoin2(NULL, "[", 1);
	while (s[++cont])
	{
		if (cont != 0)
			result = ft_strjoin2(result, ", ", 1);
		result = ft_strjoin2(result, ft_putstr_shell(s[cont]), 3);
	}
	result = ft_strjoin2(result, "]", 1);
	return (result);
}

char	*ft_printargscn_shell(char **s)
{
	size_t	cont;
	char	*result;

	if (!s)
		return (ft_putstr_shell("(NULL)"));
	cont = -1;
	result = NULL;
	while (s[++cont])
	{
		result = ft_strjoin2(result, "[", 1);
		result = ft_strjoin2(result, ft_putnbr_shell(cont, result), 3);
		result = ft_strjoin2(result, "] = [", 1);
		result = ft_strjoin2(result, ft_putstr_shell(s[cont]), 3);
		result = ft_strjoin2(result, "]\n", 1);
	}
	return (result);
}
