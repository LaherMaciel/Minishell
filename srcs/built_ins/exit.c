/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:16:26 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/22 20:19:13 by lahermaciel      ###   ########.fr       */
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

static void	handle_exit_errors(char **input)
{
	if (!is_valid_exit_code(input[1]))
	{
		ft_fdprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n",
			input[1]);
		ft_free_array(input, 0);
		clean_exit(2);
	}
	if (input[2])
	{
		ft_fdprintf(STDERR_FILENO,
			"minishell: exit: too many arguments\n");
		mshell()->exit_status = 1;
		ft_free_array(input, 0);
		return ;
	}
}

void	builtin_exit(char **input)
{
	int	status;

	ft_printf("exit\n");
	if (!input[1])
	{
		status = mshell()->exit_status;
		ft_free_array(input, 0);
		clean_exit(status);
	}
	handle_exit_errors(input);
	builtin_ex_aux(input);
	status = mshell()->exit_status;
	ft_free_array(input, 0);
	clean_exit(status);
}
