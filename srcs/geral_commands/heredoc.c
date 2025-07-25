/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:23:50 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/22 17:32:18 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_heredoc_write(int fd, char *line, int expand)
{
	char	*expanded;

	if (!expand)
	{
		expanded = expand_heredoc_vars(line);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
	}
	else if (line)
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	exec_heredoc_loop(char *delim, int fd[2], int expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			mshell()->exit_status = 2;
			close(fd[1]);
			clean_exit(2);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		exec_heredoc_write(fd[1], line, expand);
		free(line);
	}
}

static void	exec_heredoc(char *delimiter, int fd[2], int expand)
{
	close(fd[0]);
	mshell()->infile = STDIN_FILENO;
	signal(SIGINT, sig_heredoc);
	exec_heredoc_loop(delimiter, fd, expand);
	close(fd[1]);
	clean_exit(0);
}

int	check_delimiter(char *delimiter)
{
	if (!delimiter)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: syntax error near"
			" unexpected token `newline'\n");
		mshell()->exit_status = 2;
		return (0);
	}
	return (1);
}

int	handle_heredoc(char *delimiter, int fd[2], int is_quoted)
{
	pid_t	pid;
	int		status;

	if (!check_delimiter(delimiter))
		return (1);
	mshell()->heredoc = 1;
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->outfile = STDOUT_FILENO;
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	if (pipe(fd) < 0)
		return (perror(NULL), 0);
	pid = create_child_process();
	if (pid == 0)
		exec_heredoc(delimiter, fd, is_quoted);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mshell()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mshell()->exit_status = 128 + WTERMSIG(status);
	mshell()->heredoc = 0;
	mshell()->infile = fd[0];
	return (0);
}
