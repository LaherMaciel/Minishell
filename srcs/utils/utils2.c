/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:59:35 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/14 14:22:42 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_token(char **cur, char *input, t_parsing *counts)
{
	if ((counts->quote == 0 || counts->quote == 2)
		&& input[counts->i + 1] == '?')
	{
		*cur = ft_strjoin2(*cur, ft_itoa(mshell()->exit_status), 3);
		counts->i += 2;
	}
}

char	**add_token(char **res, char **cur, t_parsing *counts, char *str)
{
	res = add_current(res, cur, &counts->k);
	res[counts->k] = ft_strdup(str);
	if (!res[counts->k])
		return (NULL);
	(counts->k)++;
	return (res);
}

void	clear_input(char **aux)
{
	int	i;
	int	j;

	i = -1;
	while (aux[++i])
	{
		j = -1;
		while (mshell()->input[++j])
		{
			if (ft_strcmp(aux[i], mshell()->input[j]) == 0)
			{
				mshell()->input = ft_rm_from_array(mshell()->input, 0, j);
				break ;
			}
		}
	}
	set_inputvalue();
}
