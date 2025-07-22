/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:32 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/19 21:08:16 by lahermaciel      ###   ########.fr       */
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

	n_flag = echo_parse_n_flag(input, &i);
	echo_print_args(input, i);
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
	int	ret;

	ret = builtins_dispatch(input);
	if (ret)
		update_(input[0]);
	return (ret);
}
