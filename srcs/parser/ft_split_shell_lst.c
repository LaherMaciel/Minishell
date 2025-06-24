/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/24 19:56:29 by karocha-         ###   ########.fr       */
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
	{
		temp_node = ft_lstnew_shell(ft_strdup(">>"), counts->quote);
		temp_node->quoted = counts->quote;
		ft_lstadd_back_shell(lst, temp_node);
		counts->i += 2;
	}
	else if (input[counts->i] == '<' && input[counts->i + 1] == '<')
	{
		temp_node = ft_lstnew_shell(ft_strdup("<<"), counts->quote);
		temp_node->quoted = counts->quote;
		ft_lstadd_back_shell(lst, temp_node);
		counts->i += 2;
	}
	else
	{
		temp_node = ft_lstnew_shell(ft_substr(input, counts->i, 1), counts->quote);
		temp_node->quoted = counts->quote;
		ft_lstadd_back_shell(lst, temp_node);
		counts->i++;
	}
	return (*lst);
}

static int	dollar_sign_lst(char **cur, char *input, t_parsing *counts)
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

static t_parsing	*process_token_lst(t_pars_lst **lst,
	t_pars_lst **new_node, char *input, t_parsing *counts)
{
	char	*val;
	char	**splitted;
	int		i;

	if (!*new_node)
		*new_node = ft_lstnew_shell(NULL, counts->quote);
	aux_token(&((*new_node)->content), input, counts);
	if ((counts->quote == 0 || counts->quote == 2) && input[counts->i] == '$')
	{
		if (get_value2(input + counts->i + 1))
		{
			val = get_value(input + counts->i + 1);
			if (counts->quote == 2)
			{
				(*new_node)->content = ft_strjoin2((*new_node)->content, val, 1);
				(*new_node)->quoted = counts->quote;
			}
			else
			{
				splitted = ft_split(val, ' ');
				i = -1;
				if ((*new_node)->content && splitted[0])
				{
					(*new_node)->content = ft_strjoin2((*new_node)->content, splitted[0], 1);
					(*new_node)->quoted = counts->quote;
					ft_lstadd_back_shell(lst, *new_node);
					*new_node = ft_lstnew_shell(NULL, 0);
					i = 0;
				}
				while (splitted[++i])
				{
					t_pars_lst *temp = ft_lstnew_shell(ft_strdup(splitted[i]), 0);
					temp->quoted = counts->quote;
					ft_lstadd_back_shell(lst, temp);
				}
				ft_free_array(splitted, 0);
			}
			free(val);
		}
		counts->i = dollar_sign_lst(&((*new_node)->content), input, counts);
	}
	else
	{
		if (((input[counts->i] == '\'' && counts->quote == 2)
			|| (input[counts->i] == '\"' && counts->quote == 1))
			|| (input[counts->i] != '\'' && input[counts->i] != '\"' && input[counts->i] != '\n'))
		{
			(*new_node)->content = ft_strjoin3((*new_node)->content, input[counts->i], 1);
			if ((*new_node)->quoted == 0 && counts->quote != 0)
				(*new_node)->quoted = 1;
		}
		counts->i++;
	}
	return (counts);
}

static t_pars_lst	*split_loop_lst(t_pars_lst **lst, char *input,
	t_parsing *counts)
{
	t_pars_lst	*new_node;

	new_node = NULL;
	while (counts->i < ft_strlen(input))
	{
		about_quotes(input, counts);
		if (counts->quote == 0
			&& (ft_strchr("|><&", input[counts->i])))
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
	{
		ft_lstadd_back_shell(lst, new_node);
	}
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
