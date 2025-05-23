/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:30 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/23 12:33:48 by lahermaciel      ###   ########.fr       */
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

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
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

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	full_path = search_command_in_path(cmd, path_env);
	if (!full_path)
		mshell()->exit_status = 127;
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
	if (error == -1)
		ft_fdprintf(STDERR_FILENO, "%s: %s\n", message, strerror(errno));
	else if (error == -3)
		ft_fdprintf(STDERR_FILENO, "minishell: %s: %s\n",
			strerror(errno), message);
	else
	{
		if (error == 0 || error == 1)
		{
			if (error == 1)
				ft_fdprintf(STDERR_FILENO, "%s\n", message);
			mshell()->exit_status = error;
		}
		else if (error == -2)
			ft_fdprintf(STDERR_FILENO, "%s\n", message);
		else if (error == -4)
		{
			ft_fdprintf(STDERR_FILENO, "minishell: %s: command not found\n",
				message);
			exit(127);
		}
		exit (mshell()->exit_status);
	}
	exit(errno);
}
