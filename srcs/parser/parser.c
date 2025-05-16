/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/05/16 18:27:14 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	about_quotes(char *input, int *quote, int i)
{
	if (*quote == 0)
	{
		if (input[i] == '\'')
			*quote = 1;
		if (input[i] == '\"')
			*quote = 2;
	}
	else if ((input[i] == '\'' && *quote == 1)
		|| (input[i] == '\"' && *quote == 2))
		*quote = 0;
}

static char	*is_special_sequence(char *str)
{
	if (str[0] == ' ')
		return (" ");
	if (str[0] == '>' && str[1] == '>')
		return (">>");
	if (str[0] == '<' && str[1] == '<')
		return ("<<");
	if (str[0] == '|' && str[1] == '|')
		return ("||");
	if (str[0] == '&' && str[1] == '&')
		return ("&&");
	if (str[0] == '|' || str[0] == '>'
		|| str[0] == '<' || str[0] == '&')
		return (ft_strjoin3(NULL, str[0], 0));
	return (NULL);
}

static char	**handle_special_chars(char *input,
	char **result, int *k, int quote)
{
	char	*sequence;

	ft_printf("input = '%c'\nk = %i\n", input[0], *k);
	sequence = is_special_sequence(input);
	if (sequence)
	{
		if (ft_strcmp(sequence, " ") == 0 && quote == 0)
		{
			ft_printf ("if (ft_strcmp(sequence(%s), " ")(%i) == 0 "
				"&& quote(%i) == 0)\n", sequence, ft_strcmp(sequence, " "), quote);
			if (result[*k])
			{
				result = ft_append_to_array(result, 0, NULL, 1);
				ft_printf("	Result[%i] = %s\n", *k, result[*k]);
				*k += 1;
				ft_printf("	New NULL array position\n");
				ft_printf("	Now k = %i\n", *k);
				ft_printf("	Result[%i] = %s\n", *k, result[*k]);
			}
			else
			{
				ft_printf("	Notting done\n");
				ft_printf("	k = %i\n", *k);
			}
		}
		else if (ft_strlen(sequence) == 2)
		{
			ft_printf("if (ft_strlen(sequence(%s))(%i) == 2)\n",
				sequence, ft_strlen(sequence));
			result = ft_append_to_array(result, 0, sequence, 1);
			ft_printf("	Added '%s'\n", sequence);
			result = ft_append_to_array(result, 0, NULL, 1);
			ft_printf("	Result[%i] = %s\n", *k, result[*k]);
			*k += 1;
			ft_printf("	New NULL array position\n");
			ft_printf("	Now k = %i\n", *k);
			ft_printf("	Result[%i] = %s\n", *k, result[*k]);
		}
		else if (ft_strlen(sequence) == 1 && ft_strcmp(sequence, " ") != 0)
		{
			ft_printf("if ft_strlen(sequence(%s))(%i) == 1 "
				"&& ft_strcmp(sequence(%s), " ")(%i) != 0\n", sequence,
				ft_strlen(sequence), sequence, ft_strcmp(sequence, " "));
			result = ft_append_to_array(result, 0, sequence, 1);
			ft_printf("	Added '%s'\n", sequence);
			result = ft_append_to_array(result, 0, NULL, 1);
			ft_printf("	Result[%i] = %s\n", *k, result[*k]);
			*k += 1;
			ft_printf("	New NULL array position\n");
			ft_printf("	Now k = %i\n", *k);
			ft_printf("	Result[%i] = %s\n", *k, result[*k]);
		}
		else
		{
			ft_printf("else sequence = '%s'\n", sequence);
			result[*k] = ft_strjoin3(result[*k], input[0], 1);
			ft_printf("	Added '%s' to the end of result[%i]\n", sequence, *k);
			ft_printf("	Now Resuly[%i] = %s\n", *k, result[*k]);
		}
	}
	else
	{
		result[*k] = ft_strjoin3(result[*k], input[0], 1);
		ft_printf("	Added '%c' to the end of result[%i]\n", input[0], *k);
		ft_printf("	Now Resuly[%i] = %s\n", *k, result[*k]);
	}
	ft_printf("\n");
	return (result);
}

char	**ft_split_minishell(char *input)
{
	int		i;
	int		k;
	int		quote;
	char	**result;
	char	*value;

	i = 0;
	quote = 0;
	k = 0;
	result = ft_calloc(3, sizeof(char *));
	if (!input || !result)
		return (NULL);
	while (input[i])
	{
		about_quotes(input, &quote, i);
		if ((quote == 0 || quote == 2) && input[i] == '$'
			&& get_value(input + i + 1))
		{
			value = get_value(input + i + 1);
			i = ft_strlen(value) + 1 + i;
			result[k] = ft_strjoin2(result[k], value, 1);
		}
		else
			result = handle_special_chars(input + i, result, &k, quote);
		i++;
	}
	return (result);
}

//ls>>test.txt|cat test.txt|grep "mini lib"
char	**parser(char *input)
{
	char	**aux;

	if (!input)
		return NULL;
	aux = ft_split_minishell(input);
	ft_printf("ft_split_minishell\n%t\n\n", aux);
	return (aux);
}

//ls>test.txt | cat test.txt | grep "mini lib"
//"ls | -a > something << dasd 'dasdasd' fhjsdlf"