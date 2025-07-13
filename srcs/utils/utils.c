/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:25 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/13 20:27:40 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Create a child process using fork().
 *
 * This function forks the current process and returns the child's PID. If fork
 * fails, it exits with an error message.
 *
 * @return int - The PID of the child process.
 */
int	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mshell()->exit_status = 1;
		handle_error_and_exit(-1, "Fork failed");
	}
	return (pid);
}

void	free_resources(void)
{
	ft_free_array(mshell()->input, 0);
	free(mshell()->input_v);
	free(mshell()->quoted);
	free_child_pids();
}

char	*free_if_fail(char **env, char **args, char *cmd_path)
{
	if (cmd_path)
		free(cmd_path);
	cmd_path = ft_strdup(args[0]);
	ft_free_array(env, 0);
	ft_free_array(args, 0);
	return (cmd_path);
}

t_export	*update_var(t_export *env, char **splitted)
{
	int	i;

	i = 0;
	while (env->var_name && env->var_name[i])
	{
		if (ft_strcmp(env->var_name[i], splitted[0]) == 0)
		{
			free(env->value[i]);
			env->value[i] = ft_strdup(splitted[1]);
			ft_free_array(splitted, 0);
			return (env);
		}
		i++;
	}
	return (NULL);
}
