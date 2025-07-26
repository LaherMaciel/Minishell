/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 14:24:50 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_handling(int pipefd[2], char **aux)
{
	if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 1)
		close(pipefd[1]);
	else
		mshell()->outfile = pipefd[1];
	if (mshell()->infile != STDIN_FILENO)
	{
		if (dup2(mshell()->infile, STDIN_FILENO) < 0)
			handle_error_and_exit(-1, "pipe dup2 failed for input_fd");
	}
	if (mshell()->outfile != STDOUT_FILENO)
	{
		if (dup2(mshell()->outfile, STDOUT_FILENO) < 0)
			handle_error_and_exit(-1, "pipe dup2 failed for output_fd");
	}
	if (aux && builtins(aux))
	{
		ft_free_array(aux, 0);
		clean_exit(mshell()->exit_status);
	}
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	execute_simple_command(aux, mshell()->infile, mshell()->outfile);
}

void	parent_handling(pid_t pid, int pipefd[2])
{
	close(pipefd[1]);
	add_child_pid(pid);
	if (mshell()->outfile != STDOUT_FILENO)
	{
		close(mshell()->outfile);
		mshell()->outfile = STDOUT_FILENO;
	}
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
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
		child_handling(pipefd, aux);
	}
	else
		parent_handling(pid, pipefd);
	mshell()->redirected = 0;
}

char	**pipe_dupped_arr(int index)
{
	char	**aux;
	int		i;

	aux = NULL;
	if (!mshell()->input || index >= (int) ft_arraylen(mshell()->input))
		return (NULL);
	rm_index(index);
	if (index == 0)
		return (NULL);
	i = -1;
	while (++i < index)
		if (mshell()->input_v[i] == 1 || mshell()->input_v[i] == 2)
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
		aux = pipe_dupped_arr(index);
		piper(aux);
		ft_free_array(aux, 0);
	}
	return (0);
}
