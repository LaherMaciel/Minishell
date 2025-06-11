/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:23:50 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/11 10:14:30 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_heredoc(char *delimiter, int fd[2])
{
	char	*line;

	close(fd[0]);
	signal(SIGINT, sig_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			mshell()->exit_status = 2;
			close(fd[1]);
			exit(2);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

static int	check_delimiter(char *delimiter)
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

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!check_delimiter(delimiter))
		return (1);
	mshell()->heredoc = 1;
	if (pipe(fd) < 0)
		return (perror(NULL), 0);
	pid = create_child_process();
	if (pid == 0)
		exec_heredoc(delimiter, fd);
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
