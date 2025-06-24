/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:25 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/24 19:50:07 by karocha-         ###   ########.fr       */
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

void	reset_fds(void)
{
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
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
