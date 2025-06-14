/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:21:08 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/14 13:22:22 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_export	*init_env(char **org_env)
{
	t_export	*expt;
	char		**splitted;
	int			i;

	expt = mshell()->env;
	if (!expt)
		return (NULL);
	expt->var_name = ft_calloc(sizeof(char *), (ft_arraylen(org_env) + 1));
	if (!expt->var_name)
		return (NULL);
	expt->value = ft_calloc(sizeof(char *), (ft_arraylen(org_env) + 1));
	if (!expt->value)
		return (NULL);
	i = 0;
	while (org_env[i])
	{
		splitted = ft_split(org_env[i], '=');
		if (splitted == NULL)
			return (ft_free_export(expt));
		expt->var_name[i] = ft_strdup(splitted[0]);
		expt->value[i] = ft_strdup(splitted[1]);
		ft_free_array(splitted, 0);
		i++;
	}
	return (expt);
}

char	**default_env(void)
{
	char	**env;
	int		i;

	env = ft_calloc(ft_arraylen(mshell()->env->var_name) + 1, sizeof(char *));
	i = -1;
	while (mshell()->env->var_name[++i])
	{
		env[i] = ft_strjoin(mshell()->env->var_name[i], "=");
		env[i] = ft_strjoin2(env[i], mshell()->env->value[i], 1);
	}
	return (env);
}
