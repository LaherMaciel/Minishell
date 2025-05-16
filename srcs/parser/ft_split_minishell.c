/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/16 14:39:49 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/* 
char	**test_recursive_split(char	**new_array, char *preview_split, int i)
{
	char	**second_split;

	if (ft_strnstr(preview_split[i], ">>", 0))
	{
		second_split = ft_split3(preview_split[i], ">>", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], "<<", 0))
	{
		second_split = ft_split3(preview_split[i], "<<", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], "||", 0))
	{
		second_split = ft_split3(preview_split[i], "||", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], "&&", 0))
	{
		second_split = ft_split3(preview_split[i], "&&", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], ">", 0))
	{
		second_split = ft_split3(preview_split[i], ">", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], "<", 0))
	{
		second_split = ft_split3(preview_split[i], "<", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], "|", 0))
	{
		second_split = ft_split3(preview_split[i], "|", -1);
		i = 0;
	}
	if (ft_strnstr(preview_split[i], "&", 0))
	{
		second_split = ft_split3(preview_split[i], "&", -1);
		i = 0;
	}
	else
		new_array = ft_append_to_array(new_array, second_split);
	return(new_array);
}
 */
/* 
char	**test_recursive_split(char **preview_split)
{
	char	**new_array;
	int		i;

	i = 0;
	while (preview_split[++i])
	{
		if (ft_strnstr(preview_split[i], ">>", 0))
			new_array = ft_split3(preview_split[i], ">>", -1);
		if (ft_strnstr(preview_split[i], "<<", 0))
			new_array = ft_split3(preview_split[i], "<<", -1);
		if (ft_strnstr(preview_split[i], "||", 0))
			new_array = ft_split3(preview_split[i], "||", -1);
		if (ft_strnstr(preview_split[i], "&&", 0))
			new_array = ft_split3(preview_split[i], "&&", -1);
		if (ft_strnstr(preview_split[i], ">", 0))
			new_array = ft_split3(preview_split[i], ">", -1);
		if (ft_strnstr(preview_split[i], "<", 0))
			new_array = ft_split3(preview_split[i], "<", -1);
		if (ft_strnstr(preview_split[i], "|", 0))
			new_array = ft_split3(preview_split[i], "|", -1);
		if (ft_strnstr(preview_split[i], "&", 0))
			new_array = ft_split3(preview_split[i], "&", -1);
	}
	return (new_array);
}

char	**ft_split_minishell(char *input)
{
	char	**first_split;
	char	**new_array;

	first_split = split_out_quotes(input, ' ');
	if (!first_split)
		return (NULL);
	new_array = test_recursive_split(first_split);
}
 */