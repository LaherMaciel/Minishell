/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:28:44 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/25 17:29:50 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	exp_loop(int i, char **input)
{
	char	*aux;

	if (!input || !input[1] || !input[1][0])
		return ;
	if (!ft_isalpha(input[1][0]) && input[1][0] != '_')
	{
		ft_fdprintf(mshell()->outfile, "export: `%s': not a valid identifier\n",
			input[1]);
		mshell()->exit_status = 1;
		return ;
	}
	while (input[++i])
	{
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
/* 
void	print_input(int flag, size_t i)
{
	if (flag == 1 || flag == 0)
	{
		while (mshell()->input[i])
		{
			ft_printf("input[%i] = %s\n", i, mshell()->input[i]);
			if (mshell()->input_v[i] == 3)
				ft_printf("REDIRECT OR PIPE\n");
			else if (mshell()->input_v[i] == 2)
				ft_printf("BUILTIN\n");
			else if (mshell()->input_v[i] == 1)
				ft_printf("COMMAND OR ARGUMENT\n");
			else
				ft_printf("Undefine\n");
			if (mshell()->quoted[i])
				ft_printf("inside quotes = true\n");
			else
				ft_printf("inside quotes = false\n");
			i++;
			ft_printf("\n");
		}
	}
	if (flag == 2 || flag == 0)
	{
		ft_printf("infile = %i\noutfile = %i\n",
			mshell()->infile, mshell()->outfile);
		ft_printf("exit_status = %i\nNr of child process "
			"= %i\n", mshell()->exit_status, mshell()->num_children);
	}
} */
