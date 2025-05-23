/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:25:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/22 21:333:483 by karocha-         ###   ########.fr       */
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
				ft_printf("%s=\"%s\"\n",
					mshell()->env->var_name[i],
					mshell()->env->value[i]);
			else
				ft_printf("%s=\"\"\n", mshell()->env->var_name[i]);
			i++;
		}
	}
	else
	{
		ft_printf("NEED TO ADD TEMPORARY SYSYTEM VARIABLES\n");
	}
	mshell()->exit_status = 0;
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
