/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:25 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/11 11:22:25 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	aux_purgatory(int pipefd[2], char **aux)
{
	close(pipefd[0]);
	if (mshell()->infile != STDERR_FILENO
		&& dup2(mshell()->infile, STDIN_FILENO) < 0)
	{
		if (errno == 9 && mshell()->infile == -1)
			handle_error_and_exit(0, "dup2 failed for input_fd");
		else
			handle_error_and_exit(-1, "dup2 failed for input_fd");
	}
	if (pipefd[1] != STDOUT_FILENO && dup2(pipefd[1], STDOUT_FILENO) < 0)
		handle_error_and_exit(-1, "dup2 failed for output_fd");
	if (builtins(aux))
		exit(mshell()->exit_status);
	execute_simple_command(aux, mshell()->infile, pipefd[1]);
}

void	purgatory(pid_t pid, int pipefd[2], int i, char **aux)
{
	if (pid == 0)
		aux_purgatory(pipefd, aux);
	else
	{
		close(pipefd[1]);
		add_child_pid(pid);
		if (mshell()->infile != STDIN_FILENO)
			close(mshell()->infile);
		mshell()->infile = pipefd[0];
		while (++i < 15000000)
			;
	}
}

char	**add_token(char **res, char **cur, t_parsing *counts, char *str)
{
	res = add_current(res, cur, &counts->k);
	res[counts->k] = ft_strdup(str);
	if (!res[counts->k])
		return (NULL);
	(counts->k)++;
	return (res);
}

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
