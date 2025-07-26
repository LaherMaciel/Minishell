/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:17:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 09:54:20 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_export	*export_sorter(void)
{
	t_export	*expt;
	size_t		i;
	size_t		j;

	i = 0;
	j = ft_arraylen(mshell()->env->var_name) + 1;
	expt = mshell()->expt;
	while (--j > 0)
	{
		while (i <= j && expt->var_name[i + 1])
		{
			if (ft_strcmp(expt->var_name[i],
					expt->var_name[i + 1]) > 0)
			{
				ft_swap(&expt->var_name[i],
					&expt->var_name[i + 1], 0);
				ft_swap(&expt->value[i],
					&expt->value[i + 1], 0);
			}
			else
				i++;
		}
		i = 0;
	}
	return (expt);
}

void	exp_loop(int i, char **input, char	*aux)
{
	if (!input || !input[1] || !input[1][0])
		return ;
	if (!is_valid_identifier(input[1]))
	{
		export_error(input[1]);
		return ;
	}
	while (input[++i])
	{
		if (!is_valid_identifier(input[i]))
		{
			export_error(input[i]);
			return ;
		}
		aux = ft_strnstr(input[i], "=", ft_strlen(input[i]));
		if (aux && aux[0] == '=')
		{
			mshell()->env = add_to_env(input[i]);
			mshell()->expt = add_to_export(input[i]);
		}
		else
			mshell()->expt = add_to_export(input[i]);
	}
	mshell()->expt = export_sorter();
}

void	ft_export(char **input)
{
	int		i;
	char	*env_varname;

	i = -1;
	if (!input || input[1] == NULL)
	{
		while (mshell()->expt->var_name[++i])
		{
			env_varname = get_varname2(mshell()->expt->var_name[i]);
			if (mshell()->expt->value[i] == NULL && !env_varname)
				ft_fdprintf(mshell()->outfile, "declare -x %s\n",
					mshell()->expt->var_name[i]);
			else if (mshell()->expt->value[i] != NULL)
				ft_fdprintf(mshell()->outfile, "declare -x %s=\"%s\"\n",
					mshell()->expt->var_name[i], mshell()->expt->value[i]);
			else
				ft_fdprintf(mshell()->outfile, "declare -x %s=\"\"\n",
					mshell()->expt->var_name[i]);
		}
	}
	else
		exp_loop(++i, input, "");
	mshell()->exit_status = 0;
}

t_export	*init_export(char **env)
{
	t_export	*expt;
	char		**splitted;
	int			i;

	expt = mshell()->expt;
	if (!expt)
		return (NULL);
	expt->var_name = ft_calloc(sizeof(char *), (ft_arraylen(env) + 1));
	if (!expt->var_name)
		return (NULL);
	expt->value = ft_calloc(sizeof(char *), (ft_arraylen(env) + 1));
	if (!expt->value)
		return (NULL);
	i = 0;
	while (env[i])
	{
		splitted = ft_split(env[i], '=');
		if (splitted == NULL)
			return (ft_free_export_env(expt));
		expt->var_name[i] = ft_strdup(splitted[0]);
		expt->value[i] = ft_strdup(splitted[1]);
		ft_free_array(splitted, 0);
		i++;
	}
	return (expt);
}

t_export	*add_to_export(char *str)
{
	t_export	*expt;
	char		*name;
	char		*value;
	char		*equal_sign;

	expt = mshell()->expt;
	if (!expt || !str)
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
	if (update_var(mshell()->expt, name, value))
		return (expt);
	expt = adder(expt, name, value, 0);
	return (expt);
}
