/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:25 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/26 10:45:10 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_resources(void)
{
	ft_free_array(mshell()->input, 0);
	free(mshell()->input_v);
	free(mshell()->quoted);
	free_child_pids();
}

char	*free_if_fail(char **env, char **args, char *cmd_path)
{
	if (cmd_path)
		free(cmd_path);
	cmd_path = ft_strdup(args[0]);
	ft_free_array(env, 0);
	ft_free_array(args, 0);
	return (cmd_path);
}

void	free_mshell(void)
{
	ft_free_export_env(NULL);
	ft_free_export_env(mshell()->env);
}
