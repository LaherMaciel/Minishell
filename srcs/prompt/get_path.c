/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:19:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 16:59:51 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*aux_search(char **paths, char *cmd)
{
	size_t	i;
	char	*full_path;
	int		exec_status;

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

/**
 * @brief Search for a command in PATH directories
 * 
 * @param cmd Command to search for
 * @param path_env PATH environment variable value
 * @return char* Full path if found and executable, NULL otherwise
 */
char	*search_command_in_path(char *cmd, char *path_env)
{
	char	**paths;
	char	*full_path;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = aux_search(paths, cmd);
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
		return (NULL);
	}
	else
	{
		mshell()->exit_status = 127;
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

	if (!cmd)
		return (NULL);
	path_env = get_value("PATH");
	if (!path_env)
		return (check_absolute_path(cmd));
	full_path = search_command_in_path(cmd, path_env);
	free(path_env);
	if (!full_path)
		return (check_absolute_path(cmd));
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
