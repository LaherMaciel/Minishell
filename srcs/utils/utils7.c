/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:30:42 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/12 16:29:39 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	char		*path_env;
	char		*full_path;
	struct stat	stat_buf;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		{
			handle_error_and_exit(-4, cmd);
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	path_env = get_value("PATH");
	if (!path_env)
		return (NULL);
	full_path = search_command_in_path(cmd, path_env);
	if (!full_path)
		mshell()->exit_status = 127;
	free(path_env);
	return (full_path);
}

void	aux_token(char **cur, char *input, t_parsing *counts)
{
	if ((counts->quote == 0 || counts->quote == 2)
		&& input[counts->i + 1] == '?')
	{
		*cur = ft_strjoin2(*cur, ft_itoa(mshell()->exit_status), 3);
		counts->i += 2;
	}
}

void	builtin_ex_aux(char **input)
{
	int		exit_status;
	bool	overflow;

	overflow = false;
	if (input[1])
	{
		if (!is_valid_exit_code(input[1]))
		{
			ft_fdprintf(STDERR_FILENO, "minishell: exit: %s: numeric"
				" argument required\n", input[1]);
			exit(2);
		}
		exit_status = ft_safe_atoi(input[1], &overflow);
		if (overflow)
		{
			ft_fdprintf(STDERR_FILENO, "minishell: exit: %s: numeric"
				" argument required\n", input[1]);
			exit(2);
		}
		mshell()->exit_status = normalize_exit_status(exit_status);
	}
}
