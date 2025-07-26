/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:42:36 by lawences          #+#    #+#             */
/*   Updated: 2025/07/26 17:06:43 by karocha-         ###   ########.fr       */
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

void	aux_token(char **content, char *input, t_parsing *counts)
{
	char	*str;

	str = NULL;
	if ((counts->quote == 0 || counts->quote == 2)
		&& ft_strncmp("$?", input + counts->i, 2) == 0)
	{
		*content = ft_strjoin2(*content, ft_itoa(mshell()->exit_status), 3);
		counts->i += 2;
	}
	if ((counts->quote == 0 || counts->quote == 2)
		&& ft_strcmp("$_", input + counts->i) == 0)
	{
		str = get_value("_");
		*content = ft_strjoin2(*content, str, 1);
		counts->i += 2;
		free(str);
	}
}

void	add_token_lst(t_pars_lst **lst, char **cur, char *str)
{
	t_pars_lst	*new_node;

	if (*cur)
	{
		new_node = ft_lstnew_shell(ft_strdup(*cur), 0);
		ft_lstadd_back_shell(lst, new_node);
		free(*cur);
		*cur = NULL;
	}
	new_node = ft_lstnew_shell(ft_strdup(str), 0);
	ft_lstadd_back_shell(lst, new_node);
}

int	word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_'))
		i++;
	return (i);
}
