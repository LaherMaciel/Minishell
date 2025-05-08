/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:17:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/08 22:09:57 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
void	init_environ(void)
{
	extern char	**environ;
}
 */

t_export	*init_export(char **env)
{
	t_export	*expt;
	char		**splitted;
	int			i;

	expt = mshell()->expt;
	if (!expt)
		return (NULL);
	expt->var_name = ft_calloc(sizeof(char *), (ft_arraylen(env) + 1));
	expt->value = ft_calloc(sizeof(char *), (ft_arraylen(env) + 1));
	if (!expt->value || !expt->var_name)
		return (NULL);
	i = 0;
	while (env[i])
	{
		splitted = ft_split(env[i], '=');
		if (splitted == NULL)
			return (NULL);
		expt->var_name[i] = ft_strdup(splitted[0]);
		expt->value[i] = ft_strdup(splitted[1]);
		ft_free_array(splitted);
		i++;
	}
	return (expt);
}

void	ft_export(void)
{
	int	i;

	i = 0;
	while (mshell()->expt->var_name[i])
	{
		if (mshell()->expt->value[i] != NULL)
			ft_printf("declare -x %s=\"%s\"\n",
				mshell()->expt->var_name[i],
				mshell()->expt->value[i]);
		else
			ft_printf("declare -x %s=\n",
				mshell()->expt->var_name[i]);
		i++;
	}
}

t_export	*export_sorter(void)
{
	t_export	*expt;
	char		*temp;
	int			diff;
	int			i;
	int			j;

	i = 0;
	j = ft_arraylen(mshell()->env);
	expt = mshell()->expt;
	while (j >= 0)
	{
		while (i < j)
		{
			if (expt->var_name[i + 1] != NULL)
			{
				diff = ft_strcmp(expt->var_name[i],
						expt->var_name[i + 1]);
				if (diff > 0)
				{
					temp = expt->var_name[i + 1];
					expt->var_name[i + 1]
						= ft_strdup(expt->var_name[i]);
					free(expt->var_name[i]);
					expt->var_name[i] = ft_strdup(temp);
					free(temp);
					temp = expt->value[i + 1];
					expt->value[i + 1]
						= ft_strdup(expt->value[i]);
					free(expt->value[i]);
					expt->value[i] = ft_strdup(temp);
					free(temp);
				}
				else
					i++;
			}
			else
				i++;
		}
		j--;
		i = 0;
	}
	return (expt);
}
