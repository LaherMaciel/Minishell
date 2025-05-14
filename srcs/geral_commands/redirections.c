/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:53:37 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/14 21:10:26 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Handle input redirection (`<`).
 *
 * This function opens the file specified after the `<` operator for reading and
 * sets it as the input file descriptor for the token. It also removes the
 * redirection operator and the filename from the token's commands array.
 *
 * @param t_token *token - The token structure containing commands and file
 * descriptors.
 * @param size_t index - The index of the `<` operator in the commands array.
 *
 * @return t_token* - The updated token structure.
 */
static void	handle_input_redirection(char *input)
{
	if (!input)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: ",
			"syntax error near unexpected token `newline'\n");
		return ;
	}
	mshell()->infile = open(input, O_RDONLY);
	if (mshell()->infile < 0)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: %s: %s\n",
			strerror(errno), input);
		return ;
	}
}

/**
 * @brief Handle output redirection (`>`).
 *
 * This function opens the file specified after the `>` operator for writing,
 * truncating it if it already exists. It sets the file as the output file
 * descriptor for the token and removes the redirection operator and the
 * filename from the commands array.
 *
 * @param t_token *token - The token structure containing commands and file
 * descriptors.
 * @param size_t index - The index of the `>` operator in the commands array.
 *
 * @return t_token* - The updated token structure.
 */
static void	handle_output_redirection(char *input)
{
	if (!input)
		return (ft_fdprintf(STDERR_FILENO,
				"Minishell: syntax error near unexpected token `newline'\n"));
	mshell()->outfile = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mshell()->outfile < 0)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: %s: %s\n",
			strerror(errno), input);
	}
}

/**
 * @brief Handle append redirection (`>>`).
 *
 * This function opens the file specified after the `>>` operator for appending.
 * It sets the file as the output file descriptor for the token and removes the
 * redirection operator and the filename from the commands array.
 *
 * @param t_token *token - The token structure containing commands and file
 * descriptors.
 * @param size_t index - The index of the `>>` operator in the commands array.
 *
 * @return t_token* - The updated token structure.
 */
static void	handle_append_redirection(char *input)
{
	if (!input)
		return (ft_fdprintf(STDERR_FILENO,
				"Minishell: syntax error near unexpected token `newline'\n"));
	mshell()->outfile = open(input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (mshell()->outfile < 0)
		return (ft_fdprintf(STDERR_FILENO, "Minishell: %s: ",
				"%s\n", strerror(errno), input));
}

/**
 * @brief Process redirection operators (`<`, `>`, `>>`, `<<`).
 *
 * This function checks the type of redirection operator and calls the
 * appropriate handler function to process it.
 *
 * @param t_token *token - The token structure containing commands and file
 * descriptors.
 * @param size_t index - The index of the redirection operator in the commands
 * array.
 *
 * @return t_token* - The updated token structure.
 */
void	redirection_operators_handler(char *signal, char *input)
{
	if (ft_strcmp(signal, "<<") == 0)
		handle_heredoc(input);
	else if (ft_strcmp(signal, "<") == 0)
		handle_input_redirection(input);
	else if (ft_strcmp(signal, ">>") == 0)
		handle_append_redirection(input);
	else if (ft_strcmp(signal, ">") == 0)
		handle_output_redirection(input);
}
