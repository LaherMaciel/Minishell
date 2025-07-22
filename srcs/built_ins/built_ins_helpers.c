/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/22 20:29:06 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	builtin_dispatch_core(char **input)
{
	if (ft_strncmp(input[0], "cd", 0) == 0)
		input[1] = change_directory(input[1]);
	else if (ft_strncmp(input[0], "pwd", 0) == 0)
		builtin_pwd();
	else if (ft_strcmp(input[0], "echo") == 0)
		builtin_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
		ft_env(input);
	else if (ft_strcmp(input[0], "export") == 0)
		ft_export(input);
	else if (ft_strcmp(input[0], "unset") == 0)
		ft_unset(input, 1);
	else if (ft_strcmp(input[0], "exit") == 0)
		builtin_exit(input);
	else
		return (0);
	return (1);
}

int	builtins_dispatch(char **input)
{
	return (builtin_dispatch_core(input));
}

bool	echo_parse_n_flag(char **input, int *i)
{
	bool	n_flag;
	int		j;

	n_flag = false;
	*i = 1;
	while (input[*i] && input[*i][0] == '-' && input[*i][1] == 'n')
	{
		j = 1;
		while (input[*i][j] == 'n')
			j++;
		if (input[*i][j] == '\0')
			n_flag = true;
		else
			break ;
		(*i)++;
	}
	return (n_flag);
}

void	echo_print_args(char **input, int i)
{
	while (input[i])
	{
		ft_fdprintf(mshell()->outfile, "%s", input[i]);
		if (input[i + 1])
			ft_fdprintf(mshell()->outfile, " ");
		i++;
	}
}
