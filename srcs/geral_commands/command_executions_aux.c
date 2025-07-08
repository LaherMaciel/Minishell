/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:21:10 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/08 15:50:49 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_ex_cmnd_loop(int index, char **aux)
{
	aux = dupped_arr(index);
	if (aux)
	{
		run_command(aux,
			mshell()->infile, mshell()->outfile);
		ft_free_array(aux, 0);
	}
}

void	reset_fds(void)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (mshell()->store_fd[i] != STDIN_FILENO)
			close(mshell()->store_fd[i]);
		mshell()->store_fd[i] = 0;
	}
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
}
/* 
void	store_fds(int fd)
{
	int	i;

	i = 0;
	if (mshell()->infile != STDIN_FILENO)
	{
		while (mshell()->store_fd[i] && i < 4)
			i++;
		if (i == 4)
		{
			if (mshell()->store_fd[0] != STDIN_FILENO)
				close(mshell()->store_fd[0]);
			mshell()->store_fd[0] = mshell()->store_fd[1];
			mshell()->store_fd[1] = mshell()->store_fd[2];
			mshell()->store_fd[2] = mshell()->store_fd[3];
			mshell()->store_fd[3] = mshell()->store_fd[4];
		}
		mshell()->store_fd[i] = mshell()->infile;
	}
	mshell()->infile = fd;
}
 */