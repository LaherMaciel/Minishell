/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/25 11:04:54 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_pars_lst	*handle_operator_lst(t_pars_lst **lst,
		t_pars_lst **new_node, t_parsing *counts, char *input)
{
	t_pars_lst	*temp_node;

	if ((*new_node) && (*new_node)->content)
	{
		ft_lstadd_back_shell(lst, *new_node);
		*new_node = NULL;
	}
	if (input[counts->i] == '>' && input[counts->i + 1] == '>')
		add_operator(lst, ">>", counts);
	else if (input[counts->i] == '<' && input[counts->i + 1] == '<')
		add_operator(lst, "<<", counts);
	else
	{
		temp_node = ft_lstnew_shell(ft_substr(input, counts->i, 1),
				counts->quote);
		temp_node->quoted = counts->quote;
		ft_lstadd_back_shell(lst, temp_node);
		counts->i++;
	}
	return (*lst);
}

int	dollar_sign_lst(char **cur, char *input, t_parsing *counts)
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

static t_pars_lst	*split_loop_lst(t_pars_lst **lst, char *input,
	t_parsing *counts)
{
	t_pars_lst	*new_node;

	new_node = NULL;
	while (counts->i < ft_strlen(input))
	{
		about_quotes(input, counts);
		if (counts->quote == 0 && (ft_strchr("|><&", input[counts->i])))
			*lst = handle_operator_lst(lst, &new_node, counts, input);
		else if (counts->quote == 0 && input[counts->i] == ' ')
		{
			if (new_node && new_node->content)
			{
				ft_lstadd_back_shell(lst, new_node);
				new_node = NULL;
			}
			counts->i++;
		}
		else
			counts = process_token_lst(lst, &new_node, input, counts);
	}
	if (new_node && new_node->content)
		ft_lstadd_back_shell(lst, new_node);
	else
		free(new_node);
	return (*lst);
}

void	ft_split_shell_lst(char *input)
{
	t_parsing	counts;
	t_pars_lst	*result;

	if (!input)
		return ;
	result = NULL;
	counts.i = 0;
	counts.quote = 0;
	result = split_loop_lst(&result, input, &counts);
	list_to_mshell(result, 0);
}
