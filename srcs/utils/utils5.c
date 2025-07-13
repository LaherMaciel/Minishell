/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:56:08 by lawences          #+#    #+#             */
/*   Updated: 2025/06/30 20:44:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	clean_trash(void)
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
}

static int	aux_check(int i)
{
	if (ft_strcmp(mshell()->input[i], "<<") == 0
		|| ft_strcmp(mshell()->input[i], ">>") == 0
		|| ft_strcmp(mshell()->input[i], ">") == 0)
	{
		if (ft_strcmp(mshell()->input[i + 1], ">") == 0
			|| ft_strcmp(mshell()->input[i + 1], "<") == 0
			|| ft_strcmp(mshell()->input[i + 1], ">>") == 0
			|| ft_strcmp(mshell()->input[i + 1], "<<") == 0)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n",
				mshell()->input[i + 1]);
			mshell()->exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	check_bad_specials(void)
{
	int	i;

	i = -1;
	while (mshell()->input[++i])
	{
		if (ft_strcmp(mshell()->input[i], "<<") == 0
			|| ft_strcmp(mshell()->input[i], ">>") == 0
			|| ft_strcmp(mshell()->input[i], "<") == 0)
		{
			if (ft_strcmp(mshell()->input[i + 1], "|") == 0)
			{
				ft_printf("minishell: syntax error"
					"near unexpected token `%s'\n", mshell()->input[i + 1]);
				mshell()->exit_status = 2;
				return (1);
			}
		}
		if (aux_check(i))
			return (1);
	}
	return (0);
}
