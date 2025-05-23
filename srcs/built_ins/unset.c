/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:59:19 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/23 11:43:24 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleaning(char **input, int index, int i)
{
	size_t	aux_env;
	size_t	aux_expt;

	aux_env = ft_arraylen(mshell()->env->var_name);
	aux_expt = ft_arraylen(mshell()->expt->var_name);
	while (mshell()->expt->var_name[++i])
	{
		if (ft_strcmp(input[index], mshell()->expt->var_name[i]) == 0)
		{
			mshell()->env->value = ft_rm_from_array(mshell()->env->value,
				aux_env, i);
			mshell()->env->var_name = ft_rm_from_array(mshell()->env->var_name,
				aux_env, i);
			mshell()->expt->value = ft_rm_from_array(mshell()->expt->value,
				aux_expt, i);
			mshell()->expt->var_name = ft_rm_from_array(mshell()->expt->var_name,
				aux_expt, i);
		}
	}
}

void	ft_unset(char **input, int index)
{
	if (input == NULL)
		return ;
	while (input[index])
	{
		cleaning(input, index, -1);
		index++;
	}
	mshell()->exit_status = 0;
}
