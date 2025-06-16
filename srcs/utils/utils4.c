/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:28:44 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/16 20:35:31 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_varname2(char *var_name)
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
			return (env->var_name[i]);
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

int	word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}

void	exp_loop(int i, char **input)
{
	char	*aux;

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

void	print_input(int flag, size_t i)
{
	if (flag == 1 || flag == 0)
	{
		while (mshell()->input[i])
		{
			ft_printf("input[%i] = %s\n", i, mshell()->input[i]);
			if (mshell()->input_value[i] == 3)
				ft_printf("REDIRECT OR PIPE\n");
			else if (mshell()->input_value[i] == 2)
				ft_printf("BUILTIN\n");
			else if (mshell()->input_value[i] == 1)
				ft_printf("COMMAND OR ARGUMENT\n");
			else
				ft_printf("Undefine\n");
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
}
