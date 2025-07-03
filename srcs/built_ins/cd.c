/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:21:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/03 18:29:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	no_path(char *path)
{
	char	*full_msg;

	full_msg = NULL;
	if (!check_var_name("HOME"))
	{
		ft_fdprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		mshell()->exit_status = 1;
		return ;
	}
	path = get_value("HOME");
	if (!path)
		return ;
	if (chdir(path))
	{
		full_msg = ft_strjoin("minishell: cd: ", path);
		perror(full_msg);
		free(full_msg);
		free(path);
		mshell()->exit_status = 1;
		return ;
	}
	free(path);
}

static char	*return_to_oldpwd(char *path)
{
	char	*full_msg;

	full_msg = NULL;
	if (ft_strcmp(path, "-") == 0)
	{
		free(path);
		path = get_value("OLDPWD");
		if (!path)
		{
			ft_fdprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
			mshell()->exit_status = 1;
			return (NULL);
		}
		if (chdir(path))
		{
			full_msg = ft_strjoin("minishell: cd: ", path);
			perror(full_msg);
			free(full_msg);
			free(path);
			mshell()->exit_status = 1;
			return (NULL);
		}
	}
	return (path);
}

static char	*check_and_change(char *path)
{
	char	*full_msg;

	full_msg = NULL;
	if (!path)
		no_path(path);
	else if (ft_strcmp(path, "-") == 0)
	{
		path = return_to_oldpwd(path);
		if (path)
			ft_printf("%s\n", path);
	}
	else if (chdir(path))
	{
		full_msg = ft_strjoin("minishell: cd: ", path);
		perror(full_msg);
		free(full_msg);
		mshell()->exit_status = 1;
		free(path);
		return (NULL);
	}
	return (path);
}

char	*change_directory(char *path)
{
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = NULL;
	old_pwd = NULL;
	path = check_and_change(path);
	if (!path)
		return (NULL);
	old_pwd = ft_strjoin2("OLDPWD=", get_value("PWD"), 2);
	add_to_env(old_pwd);
	add_to_export(old_pwd);
	free(old_pwd);
	new_pwd = ft_strjoin2("PWD=", getcwd(NULL, 0), 2);
	add_to_env(new_pwd);
	add_to_export(new_pwd);
	mshell()->expt = export_sorter();
	free(new_pwd);
	return (path);
}
