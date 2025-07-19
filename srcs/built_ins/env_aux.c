/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:21:08 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/19 18:12:53 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_shlvl(void)
{
	char	*shlvl_str;
	int		shlvl;
	char	*num_str;
	char	*full;

	shlvl_str = getenv("SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	num_str = ft_itoa(shlvl);
	if (!num_str)
		return ;
	full = ft_strjoin("SHLVL=", num_str);
	free(num_str);
	if (!full)
		return ;
	add_to_env(full);
	add_to_export(full);
	free(full);
}

void	start_no_env(void)
{
	char	*pwd;

	pwd = ft_strjoin2("PWD=", getcwd(NULL, 0), 2);
	add_to_env(pwd);
	add_to_env("SHLVL=1");
	add_to_env("_=/usr/bin/env");
	add_to_export(pwd);
	add_to_export("SHLVL=1");
	add_to_export("OLDPWD");
	mshell()->expt = export_sorter();
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

t_export	*adder(t_export *env, char *var_name, char *var_value, int flag)
{
	if (((var_value == NULL && flag) || ft_strlen(var_value) == 1))
	{
		if (ft_strlen(var_value) == 1)
		{
			var_value = NULL;
			env->value = ft_append_to_array(env->value,
				ft_arraylen(env->var_name) - 1, var_value, 1);
		}
		env->var_name = ft_append_to_array(env->var_name,
			ft_arraylen(env->var_name), var_name, 1);
		if (!env->var_name)
			ft_free_export(env);
	}
	else
	{
		env->var_name = ft_append_to_array(env->var_name,
			ft_arraylen(env->var_name), var_name, 1);
		if (!env->var_name)
			ft_free_export(env);
		env->value = ft_append_to_array(env->value,
			ft_arraylen(env->var_name) - 1, var_value, 1);
	}
	return (env);
}
