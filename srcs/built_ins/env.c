/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:25:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/25 15:51:31 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_export	*add_to_env(char *str)
{
	t_export	*env;
	char		**splitted;

	env = mshell()->env;
	if (!env || !str)
		return (NULL);
	splitted = ft_split(str, '=');
	if (!splitted || !splitted[0])
		return (ft_free_array(splitted, 0));
	if (update_var(env, splitted))
		return (env);
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

void	ft_env(char **input)
{
	int	i;

	i = 0;
	if (!input || input[1] == NULL)
	{
		while (mshell()->env->var_name[i])
		{
			if (mshell()->env->value[i] != NULL)
				ft_fdprintf(mshell()->outfile, "%s=%s\n",
					mshell()->env->var_name[i],
					mshell()->env->value[i]);
			else
				ft_fdprintf(mshell()->outfile, "%s=\"\"\n",
					mshell()->env->var_name[i]);
			i++;
		}
	}
	else
		ft_fdprintf(mshell()->outfile, "\ninput: %t\n", input);
	mshell()->exit_status = 0;
}

int	check_var_name(char *var_name)
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
				word_size(var_name)) == 0)
			return (i);
		i++;
	}
	return (0);
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
				word_size(var_name)) == 0)
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
				ft_strlen(env->var_name[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}
