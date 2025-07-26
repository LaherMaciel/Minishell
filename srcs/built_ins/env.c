/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:25:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 17:01:37 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_export	*add_to_env(char *str)
{
	t_export	*env;
	char		*name;
	char		*value;
	char		*equal_sign;

	env = mshell()->env;
	if (!env || !str)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		name = ft_strdup(str);
		value = NULL;
	}
	else
	{
		name = ft_substr(str, 0, equal_sign - str);
		value = ft_strdup(equal_sign + 1);
	}
	if (update_var(env, name, value))
		return (env);
	env = adder(env, name, value, 0);
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
			if (mshell()->env->value[i] != NULL
				&& mshell()->env->value[i][0] != '\0')
				ft_fdprintf(mshell()->outfile, "%s=%s\n",
					mshell()->env->var_name[i],
					mshell()->env->value[i]);
			else
				ft_fdprintf(mshell()->outfile, "%s=\"\"\n",
					mshell()->env->var_name[i]);
			i++;
		}
	}
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
