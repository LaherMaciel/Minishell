/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:19:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/27 17:22:33 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	aux_check_executable(const char *cmd, struct stat stat_buf)
{
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
			mshell()->exit_status = -4;
		else
			mshell()->exit_status = 127;
		return (-6);
	}
	if (stat(cmd, &stat_buf) != 0)
		return (-1);
	return (aux_check_executable(cmd, stat_buf));
}

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
