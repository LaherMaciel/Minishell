/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:22:59 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/14 14:47:44 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_status(char *line)
{
	if (line)
		ft_fdprintf(mshell()->outfile, "%i%s: command not found\n",
			mshell()->exit_status, line + 2);
	else
		ft_fdprintf(mshell()->outfile, "%i: command not found\n",
			mshell()->exit_status);
}

static int	ft_safe_atoi_aux2(long long result, int sign, bool *overflow)
{
	if (*overflow)
	{
		if (sign == 1)
			return (255);
		else if (sign == -1)
			return (-255);
		else
			return (0);
	}
	return ((int)(result * sign));
}

static char	*ft_safe_atoi_aux(char *ptr, int *sign)
{
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr == '-')
	{
		*sign = -1;
		ptr++;
	}
	else if (*ptr == '+')
		ptr++;
	return (ptr);
}

int	ft_safe_atoi(char *str, bool *overflow)
{
	long long	result;
	int			sign;
	char		*ptr;

	result = 0;
	sign = 1;
	ptr = str;
	*overflow = false;
	ptr = ft_safe_atoi_aux(ptr, &sign);
	while (ft_isdigit(*ptr))
	{
		if (((result * sign) == LONG_MIN / 10
				&& (*ptr - '0') > (LONG_MIN % 10) * -1)
			|| (result > (LONG_MAX - (*ptr - '0')) / 10 && sign == 1))
		{
			*overflow = true;
			break ;
		}
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	return (ft_safe_atoi_aux2(result, sign, overflow));
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
