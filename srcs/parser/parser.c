/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/05/18 11:22:16 by lahermaciel      ###   ########.fr       */
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

char	**ft_split_minishell(char *input)
{
	size_t	i;
	int		k;
	int		quote;
	char	**result;
	char	*value;
	char	*current;
	char	*temp;

	i = 0;
	k = 0;
	quote = 0;
	result = ft_calloc(100, sizeof(char *)); // Increased initial size
	temp = ft_calloc(2, sizeof(char *));
	current = NULL;
	if (!input || !result)
		return (NULL);
	while (input[i])
	{
		about_quotes(input, &quote, i);
		// Handle special sequences
		if (quote == 0)
		{
			// Check for 2-character sequences first
			if (input[i] == '>' && input[i + 1] == '>')
			{
				if (current)
				{
					result[k++] = current;
					current = NULL;
				}
				result[k++] = ft_strdup(">>");
				i += 2;
				continue ;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				if (current)
				{
					result[k++] = current;
					current = NULL;
				}
				result[k++] = ft_strdup("<<");
				i += 2;
				continue ;
			}
			// Check for single-character specials
			else if (input[i] == '|' || input[i] == '>'
				|| input[i] == '<' || input[i] == '&')
			{
				if (current)
				{
					result[k++] = current;
					current = NULL;
				}
				temp[0] = input[i];
				result[k++] = ft_strdup(temp);
				i++;
				continue ;
			}
			// Handle spaces as separators (only outside quotes)
			else if (input[i] == ' ')
			{
				if (current)
				{
					result[k++] = current;
					current = NULL;
				}
				i++;
				continue ;
			}
		}
		// Handle variables (if needed)
		if ((quote == 0 || quote == 2) && input[i] == '$' && get_value(input + i + 1))
		{
			value = get_value(input + i + 1);
			current = ft_strjoin2(current, value, 1);
			i += ft_strlen(value) + 1;
			continue ;
		}
		// Normal character - add to current string
		current = ft_strjoin3(current, input[i], 1);
		i++;
	}
	free(temp);
	// Add the last token if it exists
	if (current)
		result[k++] = current;
	return (result);
}

char	**parser(char *input)
{
	char	**aux;

	if (!input)
		return (NULL);
	aux = ft_split_minishell(input);
	ft_printf("ft_split_minishell\n\n\n%t\n\n", aux);
	return (aux);
}
//ls>>test.txt|cat test.txt|grep "mini lib"
//ls>test.txt | cat test.txt | grep "mini lib"
//"ls | -a > something << dasd 'da sd a sd' fhjsdlf"
//clear && make && valgrind ./minishell "ls | -a > something << dasd 'd as d asd' fhjsdlf"
//ls>>test.txt|cat test.txt|grep "mini lib" ls | -a > something << dasd 'd as d asd' fhjsdlf
