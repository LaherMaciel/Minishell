/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:53:37 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/22 18:31:226 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_heredoc(char *input)
{
	(void) input;
	ft_printf("handle_heredoc\n");
}

static void	handle_input_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: ",
			"syntax error near unexpected token `newline'\n");
		return ;
	}
	if (mshell()->infile != STDIN_FILENO)
		close(mshell()->infile);
	mshell()->infile = open(input, O_RDONLY);
	if (mshell()->infile < 0)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: %s: %s\n",
			strerror(errno), input);
		return ;
	}
}

static void	handle_output_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO,
			"Minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->outfile = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mshell()->outfile < 0)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: %s: %s\n",
			strerror(errno), input);
	}
}

static void	handle_append_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO,
			"Minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	if (mshell()->outfile != STDOUT_FILENO)
		close(mshell()->outfile);
	mshell()->outfile = open(input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (mshell()->outfile < 0)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: %s: ",
			"%s\n", strerror(errno), input);
		return ;
	}
}

void	redirection_operators_handler(int index)
{
	if (ft_strcmp(mshell()->input[index], "<<") == 0)
		handle_heredoc(mshell()->input[index + 1]);
	else if (ft_strcmp(mshell()->input[index], "<") == 0)
		handle_input_redirection(mshell()->input[index + 1]);
	else if (ft_strcmp(mshell()->input[index], ">>") == 0)
		handle_append_redirection(mshell()->input[index + 1]);
	else if (ft_strcmp(mshell()->input[index], ">") == 0)
		handle_output_redirection(mshell()->input[index + 1]);
	rm_indexs(index, index + 1);
}
