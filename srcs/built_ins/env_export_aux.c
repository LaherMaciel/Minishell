/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:40:42 by lawences          #+#    #+#             */
/*   Updated: 2025/07/19 20:21:59 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_export	*update_var(t_export *env, char *name, char *value)
{
	int	i;

	i = 0;
	while (env->var_name && env->var_name[i])
	{
		if (ft_strcmp(env->var_name[i], name) == 0 && value != NULL)
		{
			if (env->value[i])
				free(env->value[i]);
			if (ft_strlen(value) == 1)
				env->value[i] = NULL;
			else
				env->value[i] = ft_strdup(value);
			free(value);
			return (env);
		}
		i++;
	}
	return (NULL);
}

t_export	*adder(t_export *env, char *name, char *value, int flag)
{
	if (((value == NULL && flag) || ft_strlen(value) == 1))
	{
		if (value)
			free(value);
		value = NULL;
		env->value = ft_append_to_array(env->value,
				ft_arraylen(env->var_name) - 1, value, 1);
	}
	else
	{
		env->value = ft_append_to_array(env->value,
				ft_arraylen(env->var_name) - 1, value, 1);
	}
	if (!env->value)
		return (ft_free_export_env(env));
	env->var_name = ft_append_to_array(env->var_name,
			ft_arraylen(env->var_name) - 1, name, 1);
	if (!env->var_name)
		ft_free_export_env(env);
	return (env);
}

void	*ft_free_export_env(t_export *expt)
{
	if (expt)
	{
		if (expt->value)
			ft_free_array(expt->value, ft_arraylen(expt->var_name));
		if (expt->var_name)
			ft_free_array(expt->var_name, 0);
		free(expt);
	}
	else if (mshell()->expt)
	{
		if (mshell()->expt->value)
			ft_free_array(mshell()->expt->value,
				ft_arraylen(mshell()->expt->var_name));
		if (mshell()->expt->var_name)
			ft_free_array(mshell()->expt->var_name, 0);
		free(mshell()->expt);
		mshell()->expt = NULL;
	}
	return (NULL);
}
