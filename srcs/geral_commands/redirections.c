/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:53:37 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/25 17:14:37 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_input_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO, "minishell: "
			"syntax error near unexpected token `newline'\n");
		mshell()->exit_status = 2;
		return (mshell()->exit_status);
	}
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	mshell()->infile = open(input, O_RDONLY);
	if (mshell()->infile < 0)
	{
		mshell()->infile = STDIN_FILENO;
		ft_fdprintf(STDERR_FILENO, "minishell: %s: %s\n",
			input, strerror(errno));
		mshell()->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	handle_output_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
		mshell()->exit_status = 2;
		return (mshell()->exit_status);
	}
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->outfile = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mshell()->outfile < 0)
	{
		mshell()->outfile = STDOUT_FILENO;
		ft_fdprintf(STDERR_FILENO, "minishell: %s: %s\n",
			input, strerror(errno));
		mshell()->exit_status = errno;
		return (1);
	}
	return (0);
}

static int	handle_append_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
		mshell()->exit_status = 2;
		return (mshell()->exit_status);
	}
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->outfile = open(input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (mshell()->outfile < 0)
	{
		mshell()->outfile = STDOUT_FILENO;
		ft_fdprintf(STDERR_FILENO, "minishell: %s: %s\n",
			input, strerror(errno));
		mshell()->exit_status = errno;
		return (1);
	}
	return (0);
}

int	redirection_operators_handler(int index)
{
	int	value;
	int	fd[2];

	value = 0;
	if (ft_strcmp(mshell()->input[index], "<<") == 0)
		value = handle_heredoc(mshell()->input[index + 1], fd,
				mshell()->quoted[index + 1]);
	else if (ft_strcmp(mshell()->input[index], "<") == 0)
		value = handle_input_redirection(mshell()->input[index + 1]);
	else if (ft_strcmp(mshell()->input[index], ">>") == 0)
		value = handle_append_redirection(mshell()->input[index + 1]);
	else if (ft_strcmp(mshell()->input[index], ">") == 0)
		value = handle_output_redirection(mshell()->input[index + 1]);
	mshell()->redirected = 1;
	rm_indexs(index, index + 1);
	return (value);
}
