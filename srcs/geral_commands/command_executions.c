/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/23 13:08:13 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Execute a command with its arguments.
 *
 * This function parses the command into arguments, retrieves the full path to
 * the command, and executes it using execve(). If the command fails, it exits
 * with an error.
 *
 * @param cmds - The command to execute.
 * @param env - The environment variables.
 * @param infile - The input file descriptor.
 * @param outfile - The output file descriptor.
 */
void	execute_simple_command(char **args, int infile, int outfile)
{
	char	*cmd_path;

	if (!args || !args[0])
	{
		mshell()->exit_status = 127;
		exit(127);
	}
	cmd_path = get_command_path(args[0]);
	if (!cmd_path)
		handle_error_and_exit(-4, args[0]);
	if (infile != STDERR_FILENO)
		close(infile);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	if (mshell()->aux_env)
		ft_free_array(mshell()->aux_env, 0);
	execve(cmd_path, args, default_env());
	handle_error_and_exit(-1, "Execution failed");
}

void	run_command(char **args, int infile, int outfile)
{
	pid_t	pid;

	pid = create_child_process();
	if (pid == 0)
	{
		if (infile != STDERR_FILENO && dup2(infile, STDIN_FILENO) < 0)
		{
			if (errno == 9 && infile == -1)
				handle_error_and_exit(0, "dup2 failed for input_fd");
			else
				handle_error_and_exit(-1, "dup2 failed for input_fd");
		}
		if (outfile != STDOUT_FILENO && dup2(outfile, STDOUT_FILENO) < 0)
			handle_error_and_exit(-1, "dup2 failed for output_fd");
		execute_simple_command(args, infile, outfile);
	}
	else if (pid > 0)
	{
		mshell()->child_pids = ft_realloc(mshell()->child_pids,
			(mshell()->num_children + 1) * sizeof(int));
		mshell()->child_pids[mshell()->num_children++] = pid;
	}
	else
	{
		mshell()->exit_status = 1;
		perror("minishell: fork");
	}
}

char	*execute_commands(char *line)
{
	int		index;
	int		i;
	char	**aux;
	int		status;

	if (ft_strncmp(line, "$?", 2) == 0)
	{
		exit_status(line);
		free(line);
		return (line);
	}
	parser(line);
	while (mshell()->input[0])
	{
		index = high_priority();
		if (is_redirect(mshell()->input[index]))
		{
			if (redirection_operators_handler(index))
				break ;
		}
		else if (is_special(mshell()->input[index]))
		{
			aux = dupped_arr(index);
			handle_special(aux, index);
			rm_index(index);
		}
		else
		{
			aux = dupped_arr(index);
			if (is_builtin(aux[0]))
				builtins(aux);
			else
				run_command(aux,
					mshell()->infile, mshell()->outfile);
			ft_free_array(aux, 0);
		}
	}
	reset_fds();
	i = 0;
	while (i < mshell()->num_children)
	{
		waitpid(mshell()->child_pids[i], &status, 0);
		if (WIFEXITED(status))
			mshell()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mshell()->exit_status = 128 + WTERMSIG(status);
		i++;
	}
	free(mshell()->child_pids);
	free_resources(line);
	return (line);
}
