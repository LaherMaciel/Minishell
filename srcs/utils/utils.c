/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:30 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/07 21:12:48 by lahermaciel      ###   ########.fr       */
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
	size_t	i;          // Iterator for the directories in PATH.
	char	**paths;    // Array to store the directories in PATH.
	char	*full_path; // Full path to the command.

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path_env, ':'); // Split the PATH environment variable into individual directories.
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i]) // Iterate through each directory in PATH.
	{
		full_path = ft_strjoin(paths[i], "/"); // Construct the full path by joining the directory and the command.
		if (!full_path)
			break ;
		full_path = ft_strjoin2(full_path, cmd, 1);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0) // Check if the command is executable.
			break ;
		free(full_path); // Free the full path if the command is not executable.
		full_path = NULL;
	}
	ft_free_array(paths); // Free the array of directories.
	return (full_path); // Return the full path to the command (or NULL if not found).
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
char	*get_command_path(char *cmd, int flag)
{
	char	*path_env;   // The PATH environment variable.
	char	*full_path;  // The full path to the command.

	path_env = getenv("PATH"); // Retrieve the PATH environment variable.
	if (!path_env)
		return (NULL);
	full_path = search_command_in_path(cmd, path_env); // Search for the command in the directories listed in PATH.
	if (!full_path && flag == 0) // Print an error message if the command is not found and the flag is set.
		ft_fdprintf(2, "Minishell: command not found: %s\n", cmd);
	return (full_path); // Return the full path to the command (or NULL if not found).
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
	int	out;

	out = 1; // Default exit status.
	if (error == -1)
		ft_fdprintf(STDERR_FILENO, "%s: %s\n", message, strerror(errno));
	if (error == -2)
		ft_fdprintf(STDERR_FILENO, "%s\n", message);
	if (error == -3)
		ft_fdprintf(STDERR_FILENO, "minishell: %s: %s\n",
			strerror(errno), message);
	if (error == -4)
		ft_fdprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			message);
	if (error == 1)
		ft_fdprintf(STDERR_FILENO, "%s\n", message);
	if (error == 0 || error == 1) // Set exit status to 0 for success or informational messages.
		out = 0;
	exit(out);
}

void	export_sorter(void)
{
	int	i;
	int	diff;

	i = 0;
	while (mshell()->expt->export[i])
	{
		if (mshell()->expt->export[i + 1] != NULL)
		{
			diff = ft_strcmp(mshell()->expt->export[i],
					mshell()->expt->export[i + 1]);
			if (diff < 0)
			{
				mshell()->expt->index[i] = i;
				i = 0;
			}
		}
		i++;
	}
	return (NULL);
}
