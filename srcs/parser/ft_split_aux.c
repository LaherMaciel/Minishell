/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:42:36 by lawences          #+#    #+#             */
/*   Updated: 2025/06/19 15:46:26 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**add_current(char **res, char **cur, int *k)
{
	if (*cur)
	{
		res[*k] = *cur;
		(*k)++;
		*cur = NULL;
	}
	return (res);
}

void	aux_token(char **cur, char *input, t_parsing *counts)
{
	if ((counts->quote == 0 || counts->quote == 2)
		&& input[counts->i + 1] == '?')
	{
		*cur = ft_strjoin2(*cur, ft_itoa(mshell()->exit_status), 3);
		counts->i += 2;
	}
}

void	add_token_lst(t_pars_lst **lst, char **cur, char *str)
{
	t_pars_lst	*new_node;

	if (*cur)
	{
		new_node = ft_lstnew_shell(ft_strdup(*cur));
		new_node->value = 3;
		ft_lstadd_back_shell(lst, new_node);
		free(*cur);
		*cur = NULL;
	}
	new_node = ft_lstnew_shell(ft_strdup(str));
	new_node->value = 3;
	ft_lstadd_back_shell(lst, new_node);
}

int	word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}
