/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:19:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/24 20:00:23 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Check if a file exists and has execution permissions
 * 
 * @param path Path to the file to check
 * @return int 0 if executable, -1 if doesn't exist, 126 if no permission
 */
static int	check_executable(const char *cmd, int flag)
{
	struct stat	stat_buf;

	if (access(cmd, F_OK) != 0)
	{
		if (flag)
			mshell()->exit_status = -6;
		else
			mshell()->exit_status = 127;
		return (-6);
	}
	if (stat(cmd, &stat_buf) != 0)
		return (-1);
	if (S_ISDIR(stat_buf.st_mode))
	{
		mshell()->exit_status = -4;
		return (-4);
	}
	if (!S_ISREG(stat_buf.st_mode))
	{
		mshell()->exit_status = -5;
		return (-5);
	}
	if (access(cmd, X_OK) != 0)
	{
		mshell()->exit_status = 126;
		return (126);
	}
	return (0);
}

/**
 * @brief Search for a command in PATH directories
 * 
 * @param cmd Command to search for
 * @param path_env PATH environment variable value
 * @return char* Full path if found and executable, NULL otherwise
 */
static char	*search_command_in_path(char *cmd, char *path_env)
{
	size_t	i;
	char	**paths;
	char	*full_path;
	int		exec_status;

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
		exec_status = check_executable(full_path, 0);
		if (exec_status == 0)
			break ;
		free(full_path);
		full_path = NULL;
		if (exec_status == 126)
			break ;
	}
	ft_free_array(paths, 0);
	return (full_path);
}

char	*check_absolute_path(char *cmd)
{
	int		exec_status;

	if (ft_strchr(cmd, '/'))
	{
		exec_status = check_executable(cmd, 1);
		if (exec_status == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	else
	{
		exec_status = check_executable(cmd, 0);
		if (exec_status == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
}

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
