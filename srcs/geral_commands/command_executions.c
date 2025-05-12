/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/12 21:38:16 by lahermaciel      ###   ########.fr       */
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
void	execute_simple_command(char *cmds, int infile, int outfile)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmds, ' ');
	if (!args)
		handle_error_and_exit(-1, "Failed to parse command");
	cmd_path = get_command_path(args[0], 0);
	if (!cmd_path)
	{
		ft_free_array(args, 0);
		handle_error_and_exit(0, "");
	}
	if (infile != STDERR_FILENO)
		close(infile);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	execve(cmd_path, args, mshell()->env);
	handle_error_and_exit(-1, "Execution failed");
}

void	run_command(char *line, int infile, int outfile)
{
	int	pid;

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
		execute_simple_command(line, infile, outfile);
	}
}

char	*execute_commands(char *line)
{
	char	**input;

	input = ft_split(line, ' ');
	if (ft_strncmp(input[0], "cd", 0) == 0)
		change_directory(input[1]);
	else if (ft_strncmp(input[0], "pwd", 0) == 0)
		builtin_pwd();
	else if (ft_strcmp(input[0], "echo") == 0)
		builtin_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
	{
		if (input[1] == NULL)
			ft_printf("%t\n", mshell()->env);
		else
			ft_printf("env: %s: No such file or directory\n", input[1]);
	}
	else if (ft_strcmp(input[0], "export") == 0)
	{
		if (input[1] == NULL)
			ft_export();
		else
		{
			mshell()->expt = add_to_export(input[1]);
			mshell()->expt = export_sorter();
		}
	}
	else if (ft_strcmp(input[0], "unset") == 0)
	{
		ft_unset(input, 1);
	}
	else
		run_command(line, STDIN_FILENO, STDOUT_FILENO);
	while (wait(NULL) > 0)
		;
	ft_free_strstr(input);
	free(line);
	return (line);
}
