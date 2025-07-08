/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/08 15:51:08 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* if (read(infile, 0, 0) < 0)
			handle_error_and_exit(-1, "pipe read failed for input_fd"); */
static void	child_purgatory(int infile, int outfile, char **aux)
{
	if (infile != STDIN_FILENO)
	{
		if (dup2(infile, STDIN_FILENO) < 0)
			handle_error_and_exit(-1, "pipe dup2 failed for input_fd");
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		if (dup2(outfile, STDOUT_FILENO) < 0)
			handle_error_and_exit(-1, "pipe dup2 failed for output_fd");
		close(outfile);
	}
	if (builtins(aux))
	{
		ft_free_array(aux, 0);
		clean_exit(mshell()->exit_status);
	}
	execute_simple_command(aux);
}

void	purgatory(pid_t pid, int pipefd[2])
{
	int	i;

	i = 0;
	close(pipefd[1]);
	add_child_pid(pid);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->outfile = STDOUT_FILENO;
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
	mshell()->infile = pipefd[0];
}

void	piper(char **aux)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("minishell: pipe");
		mshell()->exit_status = 1;
		return ;
	}
	pid = create_child_process();
	if (pid == 0)
	{
		close(pipefd[0]);
		if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 0)
		{
			close(mshell()->outfile);
			mshell()->outfile = pipefd[1];
		}
		if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 1)
			close(pipefd[1]);
		else
			mshell()->outfile = pipefd[1];
		child_purgatory(mshell()->infile, mshell()->outfile, aux);
	}
	else
		purgatory(pid, pipefd);
	mshell()->redirected = 0;
}

char	**pipe_dupped_arr(int index)
{
	char	**aux;
	int		i;

	aux = NULL;
	if (index <= 0)
	{
		ft_fdprintf(STDERR_FILENO, "minishell: "
			"syntax error near unexpected token `|'\n");
		return (NULL);
	}
	if (!mshell()->input || index >= (int) ft_arraylen(mshell()->input))
		return (NULL);
	rm_index(index);
	i = -1;
	while (++i < index)
		if (mshell()->input_v[i] == 1
			|| mshell()->input_v[i] == 2)
			aux = ft_append_to_array2(aux, 0, mshell()->input[i], 1);
	if (!aux)
		return (NULL);
	clear_input(aux);
	return (aux);
}

int	pipe_handler(int index)
{
	char	**aux;

	if (ft_strcmp(mshell()->input[index], "|") == 0)
	{
		if (index == 0 && mshell()->redirected)
		{
			rm_index(index);
			aux_ex_cmnd_loop(index, NULL);
			return (0);
		}
		aux = pipe_dupped_arr(index);
		if (!aux || !aux[0])
		{
			mshell()->exit_status = 2;
			return (1);
		}
		piper(aux);
		ft_free_array(aux, 0);
	}
	return (0);
}
