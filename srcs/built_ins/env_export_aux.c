/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:40:42 by lawences          #+#    #+#             */
/*   Updated: 2025/07/21 18:43:02 by marvin           ###   ########.fr       */
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
			if (value[0] == '\0')
				env->value[i] = ft_strdup("");
			else
				env->value[i] = ft_strdup(value);
			free(value);
			free(name);
			return (env);
		}
		i++;
	}
	return (NULL);
}

t_export	*adder(t_export *env, char *name, char *value, int flag)
{
	size_t	len;

	(void)flag;
	len = ft_arraylen(env->var_name);
	env->var_name = ft_realloc_and_clear(env->var_name, sizeof(char *)
			* (len + 1), sizeof(char *) * (len + 2));
	if (!env->var_name)
		return (ft_free_export_env(env));
	env->value = ft_realloc_and_clear(env->value, sizeof(char *)
			* (len + 1), sizeof(char *) * (len + 2));
	if (!env->value)
		return (ft_free_export_env(env));
	env->var_name[len] = name;
	env->var_name[len + 1] = NULL;
	env->value[len] = value;
	env->value[len + 1] = NULL;
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
