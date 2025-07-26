/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 09:51:22 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	echo_parse_n_flag(char **input, int *i)
{
	bool	n_flag;
	int		j;

	n_flag = false;
	*i = 1;
	while (input[*i] && input[*i][0] == '-' && input[*i][1] == 'n')
	{
		j = 1;
		while (input[*i][j] == 'n')
			j++;
		if (input[*i][j] == '\0')
			n_flag = true;
		else
			break ;
		(*i)++;
	}
	return (n_flag);
}

void	echo_print_args(char **input, int i)
{
	while (input[i])
	{
		ft_fdprintf(mshell()->outfile, "%s", input[i]);
		if (input[i + 1])
			ft_fdprintf(mshell()->outfile, " ");
		i++;
	}
}
