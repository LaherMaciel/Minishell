/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:43:12 by lualbuqu          #+#    #+#             */
/*   Updated: 2025/07/22 16:47:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief used to check if the number of quotes is correct
 * @param char *str the string that will be checked
 * @return int (1) if is missing a single quote ('); 2 if its missing a double
 * quote (); 0 if all is ok
 */
static int	check_quotes(char *str)
{
	int	i;
	int	open;

	i = -1;
	open = 0;
	while (str[++i])
	{
		if (open == 0)
		{
			if (str[i] == '\'')
				open = 1;
			if (str[i] == '\"')
				open = 2;
		}
		else if ((str[i] == '\'' && open == 1)
			|| (str[i] == '\"' && open == 2))
			open = 0;
	}
	return (open);
}

char	*quotes_handler(char *line)
{
	char	*aux;
	char	*tmp;

	while (check_quotes(line) != 0)
	{
		if (check_quotes(line) == 1)
			aux = readline("squote> ");
		else
			aux = readline("dquote> ");
		if (!aux)
		{
			free(line);
			return (NULL);
		}
		tmp = line;
		line = ft_strjoin2(line, "\n", 0);
		free(tmp);
		tmp = line;
		line = ft_strjoin2(line, aux, 0);
		free(tmp);
		free(aux);
		if (!line)
			return (NULL);
	}
	return (line);
}

static int	get_input(char **line, char *prompt)
{
	*line = readline(prompt);
	if (!*line)
		return (1);
	if (*line[0] != '\0')
		add_history(*line);
	if (ft_strcmp(prompt, "dquote> ") != 0
		&& ft_strcmp(prompt, "squote> ") != 0)
	{
		*line = quotes_handler(*line);
		if (!*line)
			return (1);
	}
	else
		return (3);
	return (0);
}

/**
 * @brief
 * 
 * @param char *line
 * @param char **env
 * @return char *line
 */
char	*display_prompt(char *line)
{
	int	ret;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ret = get_input(&line, "minishell> ");
		if (ret == 1)
		{
			write(1, "exit\n", 5);
			return (NULL);
		}
		if (ret == 3)
			continue ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		execute_commands(line);
	}
	return (line);
}
