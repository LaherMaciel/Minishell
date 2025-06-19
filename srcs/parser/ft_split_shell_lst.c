/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/19 18:02:15 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static t_pars_lst	*handle_operator_lst(t_pars_lst **lst, char **cur, t_parsing *counts, char *input)
{
	t_pars_lst	*new_node;

	if (input[counts->i] == '>' && input[counts->i + 1] == '>')
	{
		new_node = ft_lstnew_shell(ft_strdup(">>"));
		new_node->value = 3;
		ft_lstadd_back_shell(lst, new_node);
		counts->i += 2;
	}
	else if (input[counts->i] == '<' && input[counts->i + 1] == '<')
	{
		new_node = ft_lstnew_shell(ft_strdup("<<"));
		new_node->value = 3;
		ft_lstadd_back_shell(lst, new_node);
		counts->i += 2;
	}
	else
	{
		if (*cur)
		{
			new_node = ft_lstnew_shell(ft_strdup(*cur));
			new_node->value = 3;
			ft_lstadd_back_shell(lst, new_node);
			free(*cur);
			*cur = NULL;
		}
		new_node = ft_lstnew_shell(ft_substr(input, counts->i, 1));
		new_node->value = 3;
		ft_lstadd_back_shell(lst, new_node);
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
	char **cur, char *input, t_parsing *counts)
{
	char		*val;
	char		**splitted;
	int			i;
	t_pars_lst	*new_node;

	aux_token(cur, input, counts);
	if ((counts->quote == 0 || counts->quote == 2) && input[counts->i] == '$')
	{
		if (get_value2(input + counts->i + 1))
		{
			val = get_value(input + counts->i + 1);
			if (counts->quote == 2)
				*cur = ft_strjoin2(*cur, val, 1);
			else
			{
				splitted = ft_split(val, ' ');
				i = -1;
				if (*cur && splitted[0])
				{
					*cur = ft_strjoin2(*cur, splitted[0], 1);
					new_node = ft_lstnew_shell(ft_strdup(*cur));
					new_node->value = 1;
					ft_lstadd_back_shell(lst, new_node);
					free(*cur);
					*cur = NULL;
					i = 0;
				}
				while (splitted[++i])
				{
					new_node = ft_lstnew_shell(ft_strdup(splitted[i]));
					new_node->value = 1;
					ft_lstadd_back_shell(lst, new_node);
				}
				ft_free_array(splitted, 0);
			}
			free(val);
		}
		counts->i = dollar_sign_lst(cur, input, counts);
	}
	else
	{
		if (((input[counts->i] == '\'' && counts->quote == 2)
			|| (input[counts->i] == '\"' && counts->quote == 1))
			|| (input[counts->i] != '\'' && input[counts->i] != '\"' && input[counts->i] != '\n'))
			*cur = ft_strjoin3(*cur, input[counts->i], 1);
		(counts->i)++;
	}
	return (counts);
}

static t_pars_lst	*split_loop_lst(t_pars_lst **lst, char *input, t_parsing *counts)
{
	char	*cur;

	cur = NULL;
	while (counts->i < ft_strlen(input))
	{
		about_quotes(input, counts);
		if (counts->quote == 0
			&& (ft_strchr("|><&", input[counts->i])))
			*lst = handle_operator_lst(lst, &cur, counts, input);
		else if (counts->quote == 0 && input[counts->i] == ' ')
		{
			if (cur)
			{
				ft_lstadd_back_shell(lst, ft_lstnew_shell(ft_strdup(cur)));
				free(cur);
				cur = NULL;
			}
			counts->i++;
		}
		else
			counts = process_token_lst(lst, &cur, input, counts);
	}
	if (cur)
	{
		ft_lstadd_back_shell(lst, ft_lstnew_shell(ft_strdup(cur)));
		free(cur);
	}
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
	list_to_mshell(result);
}
