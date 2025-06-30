/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:19:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/30 18:37:58 by lahermaciel      ###   ########.fr       */
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
int	check_executable(const char *cmd, int flag)
{
	struct stat	stat_buf;

	if (access(cmd, F_OK) != 0)
	{
		if (ft_strlen(ft_strrchr(cmd, '/')) == 1 && flag)
			mshell()->exit_status = -7;
		else if (flag)
			mshell()->exit_status = -6;
		else
			mshell()->exit_status = 127;
		return (mshell()->exit_status);
	}
	if (stat(cmd, &stat_buf) != 0)
		return (-1);
	return (aux_check_executable(cmd, stat_buf));
}
