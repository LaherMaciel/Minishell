/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/05 21:24:05 by lawences         ###   ########.fr       */
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
void	execute_simple_command(char **args)
{
	char	*cmd_path;
	char	**env;
	int	status;

	status = 0;
	if (!args || !args[0])
	{
		mshell()->exit_status = 127;
		exit(127);
	}
	cmd_path = get_command_path(args[0]);
	if (!cmd_path)
	{
		cmd_path = free_if_fail(NULL, args, cmd_path);
		handle_error_and_exit(mshell()->exit_status, cmd_path);
	}
	signal(SIGINT, SIG_DFL);
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

	if (is_builtin(args[0]))
	{
		if (builtins(args))
			return ;
		handle_error_and_exit(1, "Built-in command failed");
	}
	pid = create_child_process();
	if (pid == 0)
	{
		if (infile != STDIN_FILENO)
		{
			if (dup2(infile, STDIN_FILENO) < 0)
				handle_error_and_exit(-1, "dup2 failed for input_fd");
			close(infile);
		}
		if (outfile != STDOUT_FILENO)
		{
			if (dup2(outfile, STDOUT_FILENO) < 0)
				handle_error_and_exit(-1, "dup2 failed for output_fd");
			close(outfile);
		}
		execute_simple_command(args);
	}
	else if (pid > 0)
		add_child_pid(pid);
}

static void	wait_for_childs(void)
{
	t_child_pid	*current;
	int			status;

	current = mshell()->child_pids;
	status = 0;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			mshell()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mshell()->exit_status = 128 + WTERMSIG(status);
		current = current->next;
		mshell()->num_children--;
	}
}

void	ex_cmnd_loop(int index, char **aux)
{
	int	count;

	count = -1;
	while (mshell()->input[0] && ++count < 20)
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
			aux_ex_cmnd_loop(index, aux);
	}
}

void	execute_commands(char *line)
{
	char		**aux;

	aux = NULL;
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
	ex_cmnd_loop(0, aux);
	reset_fds();
	wait_for_childs();
	free_resources();
}
