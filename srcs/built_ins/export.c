/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:17:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/25 17:29:58 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			if (mshell()->expt->value[i] == NULL || !env_varname)
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
		exp_loop(++i, input);
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
			return (ft_free_export(expt));
		expt->var_name[i] = ft_strdup(splitted[0]);
		expt->value[i] = ft_strdup(splitted[1]);
		ft_free_array(splitted, 0);
		i++;
	}
	return (expt);
}

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
					&expt->var_name[i + 1], 1);
				ft_swap(&expt->value[i],
					&expt->value[i + 1], 1);
			}
			else
				i++;
		}
		i = 0;
	}
	return (expt);
}

t_export	*add_to_export(char *str)
{
	t_export	*expt;
	char		**splitted;

	expt = mshell()->expt;
	if (!expt || !str)
		return (NULL);
	splitted = ft_split(str, '=');
	if (!splitted || !splitted[0])
		return (ft_free_array(splitted, 0));
	if (update_var(expt, splitted))
		return (expt);
	expt->var_name = ft_append_to_array(expt->var_name,
			ft_arraylen(expt->var_name), splitted[0], 1);
	if (!expt->var_name)
		ft_free_export(expt);
	else
		expt->value = ft_append_to_array(expt->value,
				ft_arraylen(expt->var_name) - 1, splitted[1], 1);
	if (!expt->value)
		ft_free_export(expt);
	free(splitted);
	return (expt);
}

void	*ft_free_export(t_export *expt)
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
