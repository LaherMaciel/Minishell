/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:59:19 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/14 21:24:55 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(char *input)
{
	int	i;

	i = -1;
	if (input == NULL)
		return ;
	while (mshell()->expt->var_name[++i])
	{
		if (ft_strcmp(input, mshell()->expt->var_name[i]) == 0)
		{
			mshell()->env->value = ft_rm_from_array(mshell()->env->value,
				ft_arraylen(mshell()->env->var_name), i);
			mshell()->env->var_name = ft_rm_from_array(mshell()->env->var_name,
				ft_arraylen(mshell()->env->var_name), i);
			mshell()->expt->value = ft_rm_from_array(mshell()->expt->value,
				ft_arraylen(mshell()->expt->var_name), i);
			mshell()->expt->var_name = ft_rm_from_array(mshell()->expt->var_name,
				ft_arraylen(mshell()->expt->var_name), i);
			return ;
		}
	}
}
