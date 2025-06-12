/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:25 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/12 18:10:16 by lahermaciel      ###   ########.fr       */
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

void	free_resources(void)
{
	ft_free_array(mshell()->input, 0);
	free(mshell()->input_value);
	free_child_pids();
}

void	reset_fds(void)
{
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
}
