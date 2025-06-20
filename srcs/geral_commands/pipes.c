/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/19 18:10:28 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * 
 */
static void	aux_purgatory(int pipefd[2], char **aux)
{
	close(pipefd[0]);
	if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 0)
	{
		close(mshell()->outfile);
		mshell()->outfile = pipefd[1];
	}
	else if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 1)
		close(pipefd[1]);
	else
		mshell()->outfile = pipefd[1];
	if (mshell()->infile != STDIN_FILENO
		&& dup2(mshell()->infile, STDIN_FILENO) < 0)
	{
		if (errno == 9 && mshell()->infile == -1)
			handle_error_and_exit(0, "dup2 failed for input_fd");
		else
			handle_error_and_exit(-1, "dup2 failed for input_fd");
	}
	if (mshell()->outfile != STDOUT_FILENO && dup2(mshell()->outfile,
			STDOUT_FILENO) < 0)
		handle_error_and_exit(-1, "dup2 failed for output_fd");
	if (builtins(aux))
	{
		ft_free_array(aux, 0);
		clean_exit(mshell()->exit_status);
	}
	execute_simple_command(aux, mshell()->infile, mshell()->outfile);
}

void	purgatory(pid_t pid, int pipefd[2], int i)
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
	while (i < 15000000)
		i++;
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
		aux_purgatory(pipefd, aux);
	else
		purgatory(pid, pipefd, 0);
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
		if (mshell()->input_value[i] == 1
			|| mshell()->input_value[i] == 2)
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
