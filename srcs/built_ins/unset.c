/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:59:19 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/19 17:41:28 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(char *input)
{
	int		i;
	size_t	aux_env;
	size_t	aux_expt;

	i = -1;
	aux_env = ft_arraylen(mshell()->env->var_name);
	aux_expt = ft_arraylen(mshell()->expt->var_name);
	if (input == NULL)
		return ;
	while (mshell()->expt->var_name[++i])
	{
		if (ft_strcmp(input, mshell()->expt->var_name[i]) == 0)
		{
			mshell()->env->value = ft_rm_from_array(mshell()->env->value,
				aux_env, i);
			mshell()->env->var_name = ft_rm_from_array(mshell()->env->var_name,
				aux_env, i);
			mshell()->expt->value = ft_rm_from_array(mshell()->expt->value,
				aux_expt, i);
			mshell()->expt->var_name = ft_rm_from_array(mshell()->expt->var_name,
				aux_expt, i);
			return ;
		}
	}
}
