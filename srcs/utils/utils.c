/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:30 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/30 17:03:49 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		handle_error_and_exit(-1, "Fork failed");
	return (pid);
}

/**
 * @brief Search for a command in the directories listed in the PATH environment
 * variable.
 *
 * This function splits the PATH environment variable into individual
 * directories, constructs the full path for the command, and checks if the
 * command is executable.
 *
 * @param char *cmd - The command to search for.
 * @param char *path_env - The PATH environment variable.
 *
 * @return char* - The full path to the command if found, otherwise NULL.
 */
static char	*search_command_in_path(char *cmd, char *path_env)
{
	size_t	i;
	char	**paths;
	char	*full_path;

	if (access(cmd + 1, X_OK) == 0)
		return (ft_strdup(cmd + 1));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break ;
		full_path = ft_strjoin2(full_path, cmd, 1);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
	}
	ft_free_array(paths, 0);
	return (full_path);
}

/**
 * @brief Resolve the full path of a command by checking the PATH environment
 * variable.
 *
 * This function retrieves the PATH environment variable and searches for the
 * command in the directories listed in PATH. If the command is not found and
 * the flag is set, it prints an error message.
 *
 * @param char *cmd - The command to resolve.
 * @param int flag - A flag to determine whether to print an error message if
 * the command is not found.
 *
 * @return char* - The full path to the command if found, otherwise NULL.
 */
char	*get_command_path(char *cmd)
{
	char	*path_env;
	char	*full_path;
	char	*error_msg;

	path_env = get_value("PATH");
	if (!path_env)
		return (NULL);
	full_path = search_command_in_path(cmd, path_env);
	if (!full_path)
	{
		error_msg = ft_strjoin("minishell: ", cmd);
		error_msg = ft_strjoin2(error_msg, ": command not found\n", 1);
		write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
		mshell()->exit_status = 127;
		free(error_msg);
	}
	return (full_path);
}

/**
 * @brief Handle errors and exit the program.
 *
 * This function prints an error message based on the error code and exits the
 * program with the appropriate status.
 *
 * @param int error - The error code.
 * @param char *message - The error message to print.
 */
void	handle_error_and_exit(int error, char *message)
{
	char	*full_msg;

	full_msg = NULL;
	if (error == -1)
	{
		full_msg = ft_strjoin(message, ": ");
		full_msg = ft_strjoin2(full_msg, strerror(errno), 1);
		full_msg = ft_strjoin2(full_msg, "\n", 1);
		write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
	}
	else if (error == -3)
	{
		full_msg = ft_strjoin("minishell: ", strerror(errno));
		full_msg = ft_strjoin2(full_msg, ": ", 1);
		full_msg = ft_strjoin2(full_msg, message, 1);
		full_msg = ft_strjoin2(full_msg, "\n", 1);
		write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
	}
	else
	{
		if (error == 0 || error == 1)
		{
			if (error == 1)
			{
				full_msg = ft_strjoin(message, "\n");
				write(STDERR_FILENO, message, ft_strlen(message));
			}
			mshell()->exit_status = error;
		}
		else if (error == -2)
		{
			full_msg = ft_strjoin(message, "\n");
			write(STDERR_FILENO, message, ft_strlen(message));
		}
		else if (error == -4)
		{
			full_msg = ft_strjoin("minishell: ", message);
			full_msg = ft_strjoin2(full_msg, ": command not found\n", 1);
			write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
			free(full_msg);
			exit(127);
		}
	}
	if (full_msg)
		free(full_msg);
	exit (mshell()->exit_status);
}

void	write_error_atomic(const char *msg)
{
	char	*full_msg;

	full_msg = ft_strjoin("minishell: ", msg);
	if (!full_msg)
		return ;
	write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
	free(full_msg);
}

