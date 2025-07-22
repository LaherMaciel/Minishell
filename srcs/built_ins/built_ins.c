/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:32 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/19 21:08:16 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	mshell()->exit_status = errno;
	if (path == NULL)
	{
		path = get_value("PWD");
		if (path == NULL)
		{
			perror("minishell: pwd");
			mshell()->exit_status = 1;
			return (1);
		}
	}
	ft_fdprintf(mshell()->outfile, "%s\n", path);
	free(path);
	return (0);
}

int	builtin_echo(char **input)
{
	bool	n_flag;
	int		i;
	int		j;

	n_flag = false;
	i = 1;
	while (input[i] && input[i][0] == '-' && input[i][1] == 'n')
	{
		j = 1;
		while (input[i][j] == 'n')
			j++;
		if (input[i][j] == '\0')
			n_flag = true;
		else
			break ;
		i++;
	}
	while (input[i])
	{
		ft_fdprintf(mshell()->outfile, "%s", input[i]);
		if (input[i + 1])
			ft_fdprintf(mshell()->outfile, " ");
		i++;
	}
	if (n_flag == false)
		ft_fdprintf(mshell()->outfile, "\n");
	mshell()->exit_status = 0;
	return (0);
}

void	update_(char *command)
{
	char	**update_;

	update_ = ft_calloc(3, sizeof(char *));
	update_[0] = ft_strdup("export");
	update_[1] = get_command_path(command);
	if (!update_[1])
		update_[1] = ft_strjoin2("_=", command, 0);
	else
		update_[1] = ft_strjoin2("_=", update_[1], 2);
	ft_export(update_);
	ft_free_array(update_, 0);
}

int	builtins(char **input)
{
	if (ft_strncmp(input[0], "cd", 0) == 0)
		input[1] = change_directory(input[1]);
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
	update_(input[0]);
	return (1);
}
