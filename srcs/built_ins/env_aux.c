/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:21:08 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/19 19:04:56 by lawences         ###   ########.fr       */
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
			return (ft_free_export_env(expt));
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
