/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:16:26 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/16 17:15:42 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	normalize_exit_status(int status)
{
	status %= 256;
	if (status < 0)
		status += 256;
	return (status);
}

bool	is_valid_exit_code(const char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	builtin_ex_aux(char **input)
{
	int		exit_status;
	bool	overflow;

	overflow = false;
	if (input[1])
	{
		exit_status = ft_safe_atoi(input[1], &overflow);
		if (overflow)
		{
			ft_fdprintf(STDERR_FILENO, "minishell: exit: %s: numeric"
				" argument required\n", input[1]);
			ft_free_array(input, 0);
			clean_exit(2);
		}
		else
			mshell()->exit_status = normalize_exit_status(exit_status);
	}
}

void	builtin_exit(char **input)
{
	ft_printf("exit\n");
	if (input[1])
	{
		if (!is_valid_exit_code(input[1]))
		{
			ft_fdprintf(STDERR_FILENO, "minishell: exit: %s: numeric"
				" argument required\n", input[1]);
			ft_free_array(input, 0);
			clean_exit(2);
		}
		if (ft_arraylen(input) > 2)
		{
			ft_fdprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
			mshell()->exit_status = 1;
			return ;
		}
		builtin_ex_aux(input);
	}
	ft_free_array(input, 0);
	clean_exit(mshell()->exit_status);
}
