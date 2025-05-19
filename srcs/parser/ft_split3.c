/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:32:57 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/19 17:23:00 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	word_count(const char *str, char *s)
{
	int	words;
	int	separator;
	int	i;

	words = 0;
	separator = 0;
	i = -1;
	if (ft_strnstr(str + i, s, ft_strlen(s)) == NULL && separator == 0)
	{
		separator = 1;
		words++;
	}
	while (str[++i])
	{
		if (ft_strnstr(str + i, s, ft_strlen(s)) == NULL && separator == 0)
		{
			separator = 1;
			words++;
		}
		else if (ft_strnstr(str + i, s, ft_strlen(s)))
		{
			i += ft_strlen(s) - 1;
			words++;
			separator = 0;
		}
	}
	return (words);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

size_t	init_split(char ***split, const char *str, char *s, int *i)
{
	size_t	word;

	word = 0;
	if (ft_strnstr(str, s, ft_strlen(s)))
	{
		*i += ft_strlen(s);
		if (*i <= (int)ft_strlen(str))
			*split[word++] = word_dup(s, 0, ft_strlen(s));
		ft_printf("split[%i]\n", word);
	}
	return (word);
}

/**
 * @brief Splits a string into an array of strings based on a given separator.
 *        The separator itself is also included as separate elements in the
 *        result.
 * 
 * @param str The input string to be split.
 * @param s The separator string used to split the input string.
 * @param i The starting index for the splitting process (usually initialized to
 * -1).
 * @return char** A dynamically allocated array of strings resulting from the
 *         split. Returns NULL if memory allocation fails or if the input string
 *         is NULL.
 * 
 * str = "e___entao__naquele___dia__o_jorge__aconteceu"
 * s = "___"
 * i = -1
 * 
 * result = {
 * [0] = [e]
 * [1] = [___]
 * [2] = [entao__naquele]
 * [3] = [___]
 * [4] = [dia__o_jorge__aconteceu]
 * }
 *
 */
char	**ft_split3(char const *str, char *s, int i)
{
	size_t	word;
	int		start;
	char	**split;

	start = -1;
	split = ft_calloc((word_count(str, s) + 1), sizeof(char *));
	if (!split || !str)
		return (0);
	word = init_split(&split, str, s, &i);
	while (++i <= (int)ft_strlen(str))
	{
		if (ft_strnstr(str + i, s, ft_strlen(s)) == NULL && start < 0)
			start = i;
		else if ((ft_strnstr(str + i, s, ft_strlen(s))
				|| i == (int)ft_strlen(str)) && start >= 0)
		{
			split[word++] = word_dup(str, start, i);
			i += ft_strlen(s) - 1;
			if ((word != (size_t)word_count(str, s) - 1)
				&& i < (int)ft_strlen(str))
				split[word++] = word_dup(s, 0, ft_strlen(s));
			start = -1;
		}
	}
	return (split);
}
