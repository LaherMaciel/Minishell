/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_what.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:32:11 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/25 15:33:55 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirect(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	is_special(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

int	its_what(int index)
{
	if ((is_redirect(mshell()->input[index])
			|| is_special(mshell()->input[index])) && !mshell()->quoted[index])
		return (3);
	if (is_builtin(mshell()->input[index]))
		return (2);
	return (1);
}
