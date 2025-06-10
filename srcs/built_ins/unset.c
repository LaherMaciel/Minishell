/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:59:19 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/10 18:01:37 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleaning(char **input, int index, int i)
{
	size_t		aux_env;
	size_t		aux_expt;
	t_export	*env;
	t_export	*expt;

	env = mshell()->env;
	expt = mshell()->expt;
	aux_env = ft_arraylen(mshell()->env->var_name);
	aux_expt = ft_arraylen(mshell()->expt->var_name);
	while (mshell()->env->var_name[++i])
	{
		if (ft_strcmp(input[index], mshell()->env->var_name[i]) == 0)
		{
			env->value = ft_rm_from_array(env->value,
					aux_env, i);
			env->var_name = ft_rm_from_array(env->var_name,
					aux_env, i);
		}
	}
	i = -1;
	while (mshell()->expt->var_name[++i])
	{
		if (ft_strcmp(input[index], mshell()->expt->var_name[i]) == 0)
		{
			expt->value = ft_rm_from_array(expt->value,
					aux_expt, i);
			expt->var_name = ft_rm_from_array(expt->var_name,
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
