/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:32 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/04/25 17:14:33 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/* 
void	change_directory(const char *path)
{
	// Attempt to change the directory
	if (chdir(path) != 0)
	{
		// If chdir() returns -1, an error occurred
		perror("cd");
	}
}
 */
int	builtin_cd(char *input)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*home;

	path = input;
	if (input == NULL || ft_strcmp(input, "~") == 0)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			ft_fdprintf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else if (strcmp(input, "-") == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			ft_fdprintf(2, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}

	// Save current directory for OLDPWD
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: cd");
		return (1);
	}

	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}

	// Update PWD and OLDPWD environment variables
	setenv("OLDPWD", cwd, 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

int	builtin_echo(char **input)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	// Check for -n flag
	if (input[1] != NULL && ft_strcmp(input[1], "-n") == 0)
	{
		n_flag = true;
		i++;
	}

	// Print all arguments separated by spaces
	while (input[i] != NULL)
	{
		ft_printf("%s", input[i]);
		if (input[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}

	// Print newline unless -n flag was set
	if (!n_flag)
		ft_printf("\n");
	return (0);
}
/* 
int	execute_builtin(char **input)
{
	if (ft_strncmp(input[0], "cd", 0) == 0)
		change_directory(input[1]);
	else if (ft_strcmp(input[0], "cd") == 0)
		return (builtin_cd(input));
	else if (ft_strcmp(input[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(input[0], "echo") == 0)
		return (builtin_echo(input));
	return (-1);
}
 */