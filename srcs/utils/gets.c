/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:28:44 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/26 17:07:01 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_varname(char *value)
{
	t_export	*env;
	int			i;

	if (!value)
		return (NULL);
	env = mshell()->env;
	if (!env || !env->var_name)
		return (NULL);
	i = 0;
	ft_printf("value = '%s'\n", value);
	while (env->var_name && env->var_name[i])
	{
		if (ft_strncmp(env->value[i], value,
				ft_strlen(env->value[i])) == 0)
		{
			ft_printf("Found env->value[%i]'%s' == '%s'\n"
				"var_name: '%s'\n", i, env->value[i], value, env->var_name[i]);
			return (ft_strdup(env->var_name[i]));
		}
		i++;
	}
	return (NULL);
}

char	*get_varname2(char *var_name)
{
	t_export	*env;
	int			i;

	if (!var_name)
		return (NULL);
	env = mshell()->env;
	if (!env || !env->var_name)
		return (NULL);
	i = 0;
	while (env->var_name && env->var_name[i])
	{
		if (ft_strcmp(env->var_name[i], var_name) == 0)
			return (env->var_name[i]);
		i++;
	}
	return (NULL);
}

char	*get_value(char *var_name)
{
	t_export	*env;
	int			i;

	env = mshell()->env;
	if (!env)
		return (NULL);
	i = 0;
	while (env->var_name && env->var_name[i])
	{
		if (ft_strncmp(env->var_name[i], var_name,
				word_size(var_name)) == 0
			&& ft_strcmp(env->value[i], "") != 0)
			return (ft_strdup(env->value[i]));
		i++;
	}
	return (NULL);
}

int	get_value2(char *var_name)
{
	t_export	*env;
	int			i;

	env = mshell()->env;
	if (!env)
		return (0);
	i = 0;
	while (env->var_name && env->var_name[i])
	{
		if (ft_strncmp(env->var_name[i], var_name,
				ft_strlen(env->var_name[i])) == 0
			&& ft_strcmp(env->value[i], "") != 0)
			return (1);
		i++;
	}
	return (0);
}

int	high_priority(void)
{
	int	i;
	int	index;
	int	highest;

	i = -1;
	highest = INT_MIN;
	while (mshell()->input[++i])
	{
		if (mshell()->input_v[i] > highest)
		{
			highest = mshell()->input_v[i];
			index = i;
		}
	}
	return (index);
}
