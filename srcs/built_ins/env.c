/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:25:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/19 16:28:58 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_export	*add_to_env(char *str)
{
	t_export	*env;
	char		**splitted;
	int			i;

	env = mshell()->env;
	if (!env || !str)
		return (NULL);
	splitted = ft_split(str, '=');
	if (!splitted || !splitted[0])
		return (ft_free_array(splitted, 0));
	i = 0;
	while (env->var_name && env->var_name[i])
	{
		if (ft_strcmp(env->var_name[i], splitted[0]) == 0)
		{
			free(env->value[i]);
			env->value[i] = ft_strdup(splitted[1]);
			ft_free_array(splitted, 0);
			return (env);
		}
		i++;
	}
	env->var_name = ft_append_to_array(env->var_name,
			ft_arraylen(env->var_name), splitted[0], 1);
	if (!env->var_name)
		ft_free_export(env);
	else
		env->value = ft_append_to_array(env->value,
				ft_arraylen(env->var_name) - 1, splitted[1], 1);
	if (!env->value)
		ft_free_export(env);
	free(splitted);
	return (env);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (mshell()->env->var_name[i])
	{
		if (mshell()->env->value[i] != NULL)
			ft_printf("%s=\"%s\"\n",
				mshell()->env->var_name[i],
				mshell()->env->value[i]);
		else
			ft_printf("%s=\"\"\n", mshell()->env->var_name[i]);
		i++;
	}
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
				ft_strlen(env->var_name[i])) == 0)
			return (ft_strdup(env->value[i]));
		i++;
	}
	return (NULL);
}

char	*get_varname(char *value)
{
	t_export	*env;
	int			i;

	env = mshell()->env;
	if (!env)
		return (NULL);
	i = 0;
	while (env->value && env->value[i])
	{
		if (ft_strncmp(env->value[i], value,
				ft_strlen(env->value[i])) == 0)
			return (ft_strdup(env->var_name[i]));
		i++;
	}
	return (NULL);
}
