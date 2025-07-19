/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:59:35 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/19 20:20:04 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	dup_loop(char **aux)
{
	int	i;
	int	j;

	i = 0;
	while (aux[i])
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
		i++;
	}
}

char	**dupped_arr(int index)
{
	char	**aux;

	aux = NULL;
	if (!mshell()->input || index < 0
		|| index >= (int) ft_arraylen(mshell()->input))
		return (NULL);
	index--;
	while (mshell()->input[++index])
		if (its_what(index) == 1 || its_what(index) == 2)
			aux = ft_append_to_array2(aux, 0, mshell()->input[index], 1);
	if (!aux)
		return (NULL);
	dup_loop(aux);
	set_inputvalue(index);
	return (aux);
}

static int	aux_check(int i)
{
	if (ft_strcmp(mshell()->input[i], "<<") == 0
		|| ft_strcmp(mshell()->input[i], ">>") == 0
		|| ft_strcmp(mshell()->input[i], ">") == 0)
	{
		if (ft_strcmp(mshell()->input[i + 1], ">") == 0
			|| ft_strcmp(mshell()->input[i + 1], "<") == 0
			|| ft_strcmp(mshell()->input[i + 1], ">>") == 0
			|| ft_strcmp(mshell()->input[i + 1], "<<") == 0)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n",
				mshell()->input[i + 1]);
			mshell()->exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	check_bad_specials(void)
{
	int	i;

	i = -1;
	while (mshell()->input[++i])
	{
		if (ft_strcmp(mshell()->input[i], "<<") == 0
			|| ft_strcmp(mshell()->input[i], ">>") == 0
			|| ft_strcmp(mshell()->input[i], "<") == 0)
		{
			if (ft_strcmp(mshell()->input[i + 1], "|") == 0)
			{
				ft_printf("minishell: syntax error"
					"near unexpected token `%s'\n", mshell()->input[i + 1]);
				mshell()->exit_status = 2;
				return (1);
			}
		}
		if (aux_check(i))
			return (1);
	}
	return (0);
}
