/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:59:19 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/12 21:32:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(char **input, int index)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (i == index)
		{
			mshell()->expt->value = ft_rm_from_array(mshell()->expt->value, ft_arraylen(mshell()->expt->var_name), i);
			mshell()->expt->var_name = ft_rm_from_array(mshell()->expt->var_name, ft_arraylen(mshell()->expt->var_name), i);
		}
		i++;
	}
}
