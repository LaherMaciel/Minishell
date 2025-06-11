/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:59:19 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/11 10:09:43 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	loop_clean(char **input, int index, size_t len, t_export *exp)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (ft_strcmp(input[index], exp->var_name[i]) == 0)
		{
			exp->value = ft_rm_from_array(exp->value, len, i);
			exp->var_name = ft_rm_from_array(exp->var_name, len, i);
			break ;
		}
		i++;
	}
}

static void	cleaning(char **input, int index)
{
	t_export	*env;
	t_export	*expt;
	size_t		aux_env;
	size_t		aux_expt;

	env = mshell()->env;
	expt = mshell()->expt;
	aux_env = ft_arraylen(env->var_name);
	aux_expt = ft_arraylen(expt->var_name);
	loop_clean(input, index, aux_env, env);
	loop_clean(input, index, aux_expt, expt);
}

void	ft_unset(char **input, int index)
{
	if (input == NULL)
		return ;
	while (input[index])
	{
		cleaning(input, index);
		index++;
	}
	mshell()->exit_status = 0;
}
