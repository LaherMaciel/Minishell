/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:23:50 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/04 19:24:02 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	heredoc_loop(int fd[2], char **new_input, int i)
{
	mshell()->infile = fd[0];
	mshell()->outfile = fd[1];
	execute_commands(new_input[i]);
}

static void	exec_heredoc(char *delimiter, int fd[2])
{
	int		i;
	char	*line;
	char	**new_input;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			mshell()->exit_status = 2;
			return ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		new_input = ft_append_to_array(new_input, 0, line, 0);
	}
	i = -1;
	while (new_input[++i])
		heredoc_loop(fd, new_input, i);
	free(new_input);
	exit(mshell()->exit_status);
}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	mshell()->heredoc = 1;
	if (pipe(fd) < 0)
		return (perror(NULL), 0);
	pid = create_child_process();
	if (pid == 0)
		exec_heredoc(delimiter, fd);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mshell()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mshell()->exit_status = 128 + WTERMSIG(status);
	}
	mshell()->heredoc = 0;
	return (0);
}
