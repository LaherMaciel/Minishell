/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/05 21:58:31 by lahermaciel      ###   ########.fr       */
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
void	execute_simple_command(char *cmds, char **env, int infile, int outfile)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmds, ' ');
	if (!args)
		handle_error_and_exit(-1, "Failed to parse command");
	cmd_path = get_command_path(args[0], 0);
	if (!cmd_path)
	{
		ft_free_array(args);
		handle_error_and_exit(0, "");
	}
	if (infile != STDERR_FILENO)
		close(infile);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	execve(cmd_path, args, env);
	handle_error_and_exit(-1, "Execution failed");
}

void	run_command(char *line, char **env, int infile, int outfile)
{
	int	pid;

	pid = create_child_process();
	if (pid == 0)
		execute_simple_command(line, env, infile, outfile);
}

char	*execute_commands(char *line, char **env)
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
		ft_printf("%t\n", env);
	else
		run_command(line, env, STDIN_FILENO, STDOUT_FILENO);
	while (wait(NULL) > 0)
		;
	ft_free_strstr(input);
	free(line);
	return (line);
}
