/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:25:54 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/19 20:12:57 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_export	*add_to_env(char *str)
{
	t_export	*env;
	char		*name;
	char		*value;

	env = mshell()->env;
	if (!env || !str)
		return (NULL);
	value = ft_strdup(ft_strnstr(str, "=", ft_strlen(str)));
	if (!value)
		name = ft_strdup(str);
	else if (ft_strlen(value) == 1)
		name = ft_substr(str, 0, ft_strlen(str) - 1);
	else
	{
		value = ft_strdup(value + 1);
		name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(value) - 1);
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
