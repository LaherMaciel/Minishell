/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:32 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/11 20:20:08 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_directory(char *path)
{
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = NULL;
	old_pwd = NULL;
	check_and_change(path);
	old_pwd = ft_strjoin2("OLDPWD=", get_value("PWD"), 2);
	add_to_env(old_pwd);
	add_to_export(old_pwd);
	free(old_pwd);
	new_pwd = ft_strjoin2("PWD=", getcwd(NULL, 0), 2);
	add_to_env(new_pwd);
	add_to_export(new_pwd);
	free(new_pwd);
}

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	mshell()->exit_status = errno;
	if (path == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_fdprintf(mshell()->outfile, "%s\n", path);
	free(path);
	return (0);
}

int	builtin_echo(char **input)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (input[1] != NULL && ft_strcmp(input[1], "-n") == 0)
	{
		n_flag = true;
		i++;
	}
	while (input[i])
	{
		ft_fdprintf(mshell()->outfile, "%s", input[i]);
		if (input[i + 1] != NULL)
			ft_fdprintf(mshell()->outfile, " ");
		i++;
	}
	if (!n_flag)
		ft_fdprintf(mshell()->outfile, "\n");
	mshell()->exit_status = 0;
	return (0);
}

void	builtin_exit(char **input)
{
	ft_printf("exit\n");
	if (ft_arraylen(input) > 2)
	{
		ft_fdprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		mshell()->exit_status = 1;
		return ;
	}
	builtin_ex_aux(input);
	exit(mshell()->exit_status);
}

int	builtins(char **input)
{
	if (ft_strncmp(input[0], "cd", 0) == 0)
		change_directory(input[1]);
	else if (ft_strncmp(input[0], "pwd", 0) == 0)
		builtin_pwd();
	else if (ft_strcmp(input[0], "echo") == 0)
		builtin_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
		ft_env(input);
	else if (ft_strcmp(input[0], "export") == 0)
		ft_export(input);
	else if (ft_strcmp(input[0], "unset") == 0)
		ft_unset(input, 1);
	else if (ft_strcmp(input[0], "exit") == 0)
		builtin_exit(input);
	else
		return (0);
	return (1);
}
