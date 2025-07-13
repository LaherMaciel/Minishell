/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/13 19:19:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * 
 */
static void	child_purgatory(int pipefd[2], char **aux)
{
	if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 1)
		close(pipefd[1]);
	else
		mshell()->outfile = pipefd[1];
	if (mshell()->infile != STDIN_FILENO)
	{
		/* ft_printf_shell(YELLOW"Closing child_purgatory infile:"
			" %i\n"DEFAULT_COLOR, mshell()->infile); */
		if (dup2(mshell()->infile, STDIN_FILENO) < 0)
			handle_error_and_exit(-1, "pipe dup2 failed for input_fd");
		close(mshell()->infile);
	}
	if (mshell()->outfile != STDOUT_FILENO)
	{
		/* ft_printf_shell(YELLOW"Closing child_purgatory outfile: "
			"%i\n"DEFAULT_COLOR, mshell()->outfile); */
		if (dup2(mshell()->outfile, STDOUT_FILENO) < 0)
			handle_error_and_exit(-1, "pipe dup2 failed for output_fd");
		close(mshell()->outfile);
	}
	if (builtins(aux))
	{
		ft_free_array(aux, 0);
		clean_exit(mshell()->exit_status);
	}
	execute_simple_command(aux, mshell()->infile, mshell()->outfile);
}

void	purgatory(pid_t pid, int pipefd[2])
{
	/* ft_printf_shell(RED"PURGATORY\n"ORANGE"current infile: %i\n"
		YELLOW"new infile: %i\n"ORANGE"current outfile: %i\n"DEFAULT_COLOR,
		mshell()->infile, pipefd[0], mshell()->outfile);
	ft_printf_shell(RED"Closing purgatory pipefd[1]: "
		"%i\n"DEFAULT_COLOR, pipefd[1]); */
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
		/* ft_printf_shell(BLUE"child_purgatory\n"GRAY"current infile: %i\ncurrent"
			" outfile: %i\n"CYAN"new_oufile: %i "GREEN"LINKED TO "YELLOW"infile"
			": %i\n\nclosing child_purgatory pipefd[0]: %i\n"DEFAULT_COLOR,
			mshell()->infile, mshell()->outfile, pipefd[1], pipefd[0], pipefd[0]); */
		close(pipefd[0]);
		if (mshell()->outfile != STDOUT_FILENO && mshell()->redirected == 0)
		{
			close(mshell()->outfile);
			mshell()->outfile = pipefd[1];
		}
		child_purgatory(pipefd, aux);
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
