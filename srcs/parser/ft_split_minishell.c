/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/19 15:21:32 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
static char	**handle_operator(char **res, char **cur, t_parsing *counts,
	char *input)
{
	if (input[counts->i] == '>' && input[counts->i + 1] == '>')
	{
		res = add_token(res, cur, counts, ">>");
		counts->i += 2;
	}
	else if (input[counts->i] == '<' && input[counts->i + 1] == '<')
	{
		res = add_token(res, cur, counts, "<<");
		counts->i += 2;
	}
	else
	{
		res = add_current(res, cur, &counts->k);
		res[counts->k] = ft_calloc(2, sizeof(char));
		if (!res[counts->k])
			return (NULL);
		res[counts->k][0] = input[(counts->i)++];
		(counts->k)++;
	}
	return (res);
}

static int	dollar_sign(char **cur, char *input, t_parsing *counts)
{
	if (word_size(input + counts->i + 1))
		counts->i += word_size(input + counts->i + 1) + 1;
	else
	{
		*cur = ft_strjoin3(*cur, input[counts->i], 1);
		counts->i++;
	}
	return (counts->i);
}

static t_parsing	*process_token(char **cur, char *input, t_parsing *counts)
{
	char	*val;

	aux_token(cur, input, counts);
	if ((counts->quote == 0 || counts->quote == 2) && input[counts->i] == '$')
	{
		if (get_value2(input + counts->i + 1))
		{
			val = get_value(input + counts->i + 1);
			*cur = ft_strjoin2(*cur, val, 1);
			free(val);
		}
		counts->i = dollar_sign(cur, input, counts);
	}
	else
	{
		if (input[counts->i] != '\'' && input[counts->i] != '\"'
			&& input[counts->i] != '\n')
			*cur = ft_strjoin3(*cur, input[counts->i], 1);
		(counts->i)++;
	}
	return (counts);
}

static char	**split_loop(char **res, char *input, t_parsing *counts)
{
	char	*cur;

	cur = NULL;
	while (counts->i < ft_strlen(input))
	{
		about_quotes(input, counts);
		if (counts->quote == 0
			&& (ft_strchr("|><&", input[counts->i])))
			res = handle_operator(res, &cur, counts, input);
		else if (counts->quote == 0 && input[counts->i] == ' ')
		{
			res = add_current(res, &cur, &counts->k);
			counts->i++;
		}
		else
			counts = process_token(&cur, input, counts);
	}
	if (cur)
		res[(counts->k)++] = cur;
	return (res);
}

char	**ft_split_minishell(char *input)
{
	t_parsing	counts;
	char		**result;

	if (!input)
		return (NULL);
	result = ft_calloc(100, sizeof(char *));
	if (!result)
		return (NULL);
	counts.k = 0;
	counts.i = 0;
	counts.quote = 0;
	result = split_loop(result, input, &counts);
	return (result);
}
*/