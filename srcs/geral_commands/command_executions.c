/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/24 12:19:10 by lahermaciel      ###   ########.fr       */
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
		exit(127);
	}
	cmd_path = get_command_path(args[0]);
	if (!cmd_path)
	{
		cmd_path = ft_strdup(args[0]);
		ft_free_array(args, 0);
		handle_error_and_exit(mshell()->exit_status, cmd_path);
	}
	if (infile != STDIN_FILENO)
		close(infile);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	signal(SIGINT, SIG_DFL);
	env = default_env();
	execve(cmd_path, args, env);
	handle_error_and_exit(-1, "Execution failed");
}

void	run_command(char **args, int infile, int outfile)
{
	pid_t	pid;

	if (is_builtin(args[0]))
	{
		if (builtins(args))
			return ;
		else
			handle_error_and_exit(1, "Built-in command failed");
	}
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
	int count = -1;

	while (mshell()->input[0] && ++count < 20)
	{
		index = high_priority();
		/* ft_printf("index = %i\n", index);
		print_input(0, 0); */
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
		{
			aux = dupped_arr(index);
			if (aux)
			{
				run_command(aux,
					mshell()->infile, mshell()->outfile);
				ft_free_array(aux, 0);
			}
		}
	}
}

char	*execute_commands(char *line)
{
	char		**aux;

	aux = NULL;
	if (ft_strncmp(line, "$?", 2) == 0)
	{
		exit_status(line);
		free(line);
		return (line);
	}
	parser(line);
	ex_cmnd_loop(0, aux);
	reset_fds();
	wait_for_childs();
	free_resources();
	return (line);
}
