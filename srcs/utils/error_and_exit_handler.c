/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:30 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/14 16:52:24 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_error_atomic(const char *msg)
{
	char	*full_msg;

	full_msg = ft_strjoin("minishell: ", msg);
	if (!full_msg)
		return ;
	write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
	free(full_msg);
}

static char	*conditioner(int error, char *message, char *full_msg)
{
	if (error == -4)
	{
		full_msg = ft_strjoin("minishell: ", message);
		full_msg = ft_strjoin2(full_msg, ": Is a directory\n", 1);
		write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
		mshell()->exit_status = 126;
	}
	else if (error == 126)
	{
		full_msg = ft_strjoin("minishell: ", message);
		full_msg = ft_strjoin2(full_msg, ": Is a file\n", 1);
		write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
		free(message);
	}
	else if (error == 127)
	{
		full_msg = ft_strjoin("minishell: ", message);
		full_msg = ft_strjoin2(full_msg, ": command not found\n", 1);
		write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
		free(message);
	}
	return (full_msg);
}

static char	*aux_error_exit(int error, char *message, char *full_msg)
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
	else
		full_msg = conditioner(error, message, full_msg);
	return (full_msg);
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
	if (mshell()->heredoc)
		exit(mshell()->exit_status);
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
		full_msg = aux_error_exit(error, message, full_msg);
	if (full_msg)
		free(full_msg);
	clean_exit(mshell()->exit_status);
}
