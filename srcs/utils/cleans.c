/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleans.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:56:08 by lawences          #+#    #+#             */
/*   Updated: 2025/07/19 20:17:17 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_fds(void)
{
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
}

void	clean_exit(int exit_status)
{
	t_child_pid	*current;
	int			status;

	current = mshell()->child_pids;
	status = 0;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			mshell()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mshell()->exit_status = 128 + WTERMSIG(status);
		current = current->next;
	}
	clean_resource();
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	free_mshell();
	exit(exit_status);
}

void	clear_input(char **aux)
{
	int	i;
	int	j;

	i = -1;
	while (aux[++i])
	{
		j = -1;
		while (mshell()->input[++j])
		{
			if (ft_strcmp(aux[i], mshell()->input[j]) == 0)
			{
				mshell()->input = ft_rm_from_array(mshell()->input, 0, j);
				set_inputvalue(j);
				break ;
			}
		}
	}
}

void	clean_resource(void)
{
	free_child_pids();
	ft_free_array(mshell()->input, 0);
	free(mshell()->input_v);
	free(mshell()->quoted);
}
