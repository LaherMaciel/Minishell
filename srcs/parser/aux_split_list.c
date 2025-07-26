/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_split_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:35:48 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/25 11:03:59 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_operator(t_pars_lst **lst, char *type, t_parsing *counts)
{
	t_pars_lst	*temp_node;

	temp_node = ft_lstnew_shell(ft_strdup(type), counts->quote);
	temp_node->quoted = counts->quote;
	ft_lstadd_back_shell(lst, temp_node);
	counts->i += 2;
}

static void	handle_split_content(t_pars_lst **lst,
	t_pars_lst **new_node, char **splitted, t_parsing *counts)
{
	int			i;
	t_pars_lst	*temp;

	i = -1;
	if ((*new_node)->content && splitted[0])
	{
		(*new_node)->content = ft_strjoin2((*new_node)->content,
				splitted[0], 1);
		(*new_node)->quoted = counts->quote;
		ft_lstadd_back_shell(lst, *new_node);
		*new_node = ft_lstnew_shell(NULL, 0);
		i = 0;
	}
	while (splitted[++i])
	{
		temp = ft_lstnew_shell(ft_strdup(splitted[i]), 0);
		temp->quoted = counts->quote;
		ft_lstadd_back_shell(lst, temp);
	}
	ft_free_array(splitted, 0);
}

static void	handle_env_expansion(t_pars_lst **lst,
	t_pars_lst **new_node, char *input, t_parsing *counts)
{
	char	*val;
	char	**splitted;

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
			handle_split_content(lst, new_node, splitted, counts);
		}
		free(val);
	}
	counts->i = dollar_sign_lst(&((*new_node)->content), input, counts);
}

static void	handle_non_dollar_char(t_pars_lst **new_node,
	char *input, t_parsing *counts)
{
	if (((input[counts->i] == '\'' && counts->quote == 2)
			|| (input[counts->i] == '\"' && counts->quote == 1))
		|| (input[counts->i] != '\'' && input[counts->i] != '\"'
			&& input[counts->i] != '\n'))
	{
		(*new_node)->content = ft_strjoin3((*new_node)->content,
				input[counts->i], 1);
		if ((*new_node)->quoted == 0 && counts->quote != 0)
			(*new_node)->quoted = 1;
	}
	counts->i++;
}

t_parsing	*process_token_lst(t_pars_lst **lst,
	t_pars_lst **new_node, char *input, t_parsing *counts)
{
	if (!*new_node)
		*new_node = ft_lstnew_shell(NULL, counts->quote);
	aux_token(&((*new_node)->content), input, counts);
	if ((counts->quote == 0 || counts->quote == 2) && input[counts->i] == '$')
		handle_env_expansion(lst, new_node, input, counts);
	else
		handle_non_dollar_char(new_node, input, counts);
	return (counts);
}
