/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:40:38 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/12 16:30:26 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**add_token(char **res, char **cur, t_parsing *counts, char *str)
{
	res = add_current(res, cur, &counts->k);
	res[counts->k] = ft_strdup(str);
	if (!res[counts->k])
		return (NULL);
	(counts->k)++;
	return (res);
}

void	exit_status(char *line)
{
	if (line)
		ft_fdprintf(mshell()->outfile, "%i%s: command not found\n",
			mshell()->exit_status, line + 2);
	else
		ft_fdprintf(mshell()->outfile, "%i: command not found\n",
			mshell()->exit_status);
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

bool	is_valid_exit_code(const char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	normalize_exit_status(int status)
{
	status %= 256;
	if (status < 0)
		status += 256;
	return (status);
}
