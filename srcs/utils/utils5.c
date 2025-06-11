/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:40:38 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/11 19:20:39 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	aux_loop(char **aux, int index)
{
	aux = dupped_arr(index);
	if (aux)
	{
		if (is_builtin(aux[0]))
			builtins(aux);
		else
			run_command(aux,
				mshell()->infile, mshell()->outfile);
		ft_free_array(aux, 0);
	}
}

void	ex_cmnd_loop(int index, char **aux)
{
	while (mshell()->input[0])
	{
		index = high_priority();
		if (is_redirect(mshell()->input[index]))
		{
			if (redirection_operators_handler(index))
				break ;
		}
		else if (is_special(mshell()->input[index]))
		{
			if (handle_special(index))
				break ;
		}
		else
			aux_loop(aux, index);
	}
}

void	ex_cmnd_loop2(void)
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
}

bool	is_valid_exit_code(const char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	normalize_exit_status(int status)
{
	status %= 256;
	if (status < 0)
		status += 256;
	return (status);
}
