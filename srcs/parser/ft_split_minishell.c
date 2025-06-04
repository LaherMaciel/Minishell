/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/04 19:22:13 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**add_token(char **res, char **cur, int *k, char *str)
{
	res = add_current(res, cur, k);
	res[*k] = ft_strdup(str);
	if (!res[*k])
		return (NULL);
	(*k)++;
	return (res);
}

static char	**handle_operator(char **res, char **cur, int *k,
	char *input, size_t *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		res = add_token(res, cur, k, ">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		res = add_token(res, cur, k, "<<");
		*i += 2;
	}
	else
	{
		res = add_current(res, cur, k);
		res[*k] = ft_calloc(2, sizeof(char));
		if (!res[*k])
			return (NULL);
		res[*k][0] = input[(*i)++];
		(*k)++;
	}
	return (res);
}

static void	process_token(char **cur, char *input, size_t *i, int quote)
{
	char	*val;

	if ((quote == 0 || quote == 2) && input[*i + 1] == '?')
	{
		*cur = ft_strjoin2(*cur, ft_itoa(mshell()->exit_status), 3);
		*i += ft_strlen(*cur) + 1;
	}
	if ((quote == 0 || quote == 2) && input[*i] == '$')
	{
		if (get_value2(input + *i + 1))
		{
			val = get_value(input + *i + 1);
			*cur = ft_strjoin2(*cur, val, 1);
			free(val);
		}
		*i += word_size(input + *i + 1) + 1;
	}
	else
	{
		if (input[*i] != '\'' && input[*i] != '\"')
			*cur = ft_strjoin3(*cur, input[*i], 1);
		(*i)++;
	}
}

static char	**split_loop(char **res, char *input, int *k)
{
	size_t	i;
	int		quote;
	char	*cur;

	i = 0;
	quote = 0;
	cur = NULL;
	while (input[i])
	{
		about_quotes(input, &quote, i);
		if (quote == 0 && (ft_strchr("|><&", input[i])))
			res = handle_operator(res, &cur, k, input, &i);
		else if (quote == 0 && input[i] == ' ')
		{
			res = add_current(res, &cur, k);
			i++;
		}
		else
			process_token(&cur, input, &i, quote);
	}
	if (cur)
		res[(*k)++] = cur;
	return (res);
}

char	**ft_split_minishell(char *input)
{
	char	**result;
	int		k;

	if (!input)
		return (NULL);
	result = ft_calloc(100, sizeof(char *));
	if (!result)
		return (NULL);
	k = 0;
	result = split_loop(result, input, &k);
	return (result);
}
