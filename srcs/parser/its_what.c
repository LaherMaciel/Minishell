/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_what.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:32:11 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/16 14:52:40 by lawences         ###   ########.fr       */
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

int	its_what(char *str)
{
	if (is_redirect(str) || is_special(str))
		return (3);
	if (is_builtin(str))
		return (2);
	return (1);
}
