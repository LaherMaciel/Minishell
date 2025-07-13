/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:21:10 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/13 20:27:42 by lahermaciel      ###   ########.fr       */
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
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
}
