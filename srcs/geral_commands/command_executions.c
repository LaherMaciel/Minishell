/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 14:24:30 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	char	**env;

	if (!args || !args[0])
	{
		mshell()->exit_status = 127;
		clean_exit(127);
	}
	cmd_path = get_command_path(args[0]);
	if (!cmd_path)
	{
		cmd_path = free_if_fail(NULL, args, cmd_path);
		handle_error_and_exit(mshell()->exit_status, cmd_path);
	}
	if (infile != STDIN_FILENO)
		close(infile);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	env = default_env();
	execve(cmd_path, args, env);
	cmd_path = free_if_fail(env, args, cmd_path);
	if (errno == 8)
		handle_error_and_exit(126, cmd_path);
	handle_error_and_exit(-1, cmd_path);
}

void	run_command(char **args, int infile, int outfile)
{
	pid_t	pid;

	if (builtins(args))
		return ;
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
		update_(args[0]);
		add_child_pid(pid);
	}
}

void	aux_ex_cmnd_loop(int index)
{
	char	**aux;

	aux = dupped_arr(index);
	if (aux)
	{
		run_command(aux,
			mshell()->infile, mshell()->outfile);
		ft_free_array(aux, 0);
	}
}

void	ex_cmnd_loop(void)
{
	int	index;

	index = 0;
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
			if (pipe_handler(index))
				break ;
		}
		else
			aux_ex_cmnd_loop(index);
	}
}

void	execute_commands(char *line)
{
	if (ft_strncmp(line, "$?", 2) == 0)
	{
		exit_status(line);
		free(line);
		return ;
	}
	parser(line);
	if (check_bad_specials())
	{
		free_resources();
		return ;
	}
	ex_cmnd_loop();
	reset_fds();
	wait_for_childs();
	free_resources();
}
