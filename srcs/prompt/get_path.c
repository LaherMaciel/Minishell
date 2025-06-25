/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:19:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/25 10:09:50 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Get full path to command with permission checking
 * 
 * @param cmd Command to locate
 * @return char* Full path if found and executable, NULL otherwise
 */
char	*get_command_path(char *cmd)
{
	char	*path_env;
	char	*full_path;

	path_env = get_value("PATH");
	if (!path_env)
	{
		mshell()->exit_status = 127;
		ft_fdprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", cmd);
		return (NULL);
	}
	full_path = search_command_in_path(cmd, path_env);
	free(path_env);
	if (!full_path)
		return (check_absolute_path(cmd));
	return (full_path);
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
 *//* 
static char	*search_command_in_path(char *cmd, char *path_env)
{
	size_t	i;
	char	**paths;
	char	*full_path;

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

char	*check_input_type(char *cmd)
{
	struct stat	stat_buf;

	if (stat(cmd, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		mshell()->exit_status = -4;
	else if (stat(cmd, &stat_buf) == 0 && !S_ISREG(stat_buf.st_mode))
		mshell()->exit_status = 126;
	else
		return (ft_strdup(cmd));
	return (NULL);
}
 */
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
 *//* 
char	*get_command_path(char *cmd)
{
	char		*path_env;
	char		*full_path;

	if (access(cmd, X_OK) == 0)
		return (check_input_type(cmd));
	path_env = get_value("PATH");
	if (!path_env)
		return (NULL);
	full_path = search_command_in_path(cmd, path_env);
	if (!full_path)
		mshell()->exit_status = 127;
	free(path_env);
	return (full_path);
}
 */