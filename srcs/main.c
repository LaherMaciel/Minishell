/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/07 21:10:50 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mshell	*mshell(void)
{
	static t_mshell	mshell;

	return (&mshell);
}

void	init_shell(void)
{
	//init_environ();
	mshell()->expt->export = NULL;
	mshell()->env = NULL;
}

static void	receive_input(void)
{
	char	*line;

	while (1)
	{
		line = display_prompt(NULL);
		if (!line)
			break ;
	}
}

int	main(int argv, char **argc, char **env)
{
	(void)argv;
	(void)argc;
	init_shell();
	mshell()->env = env;
	mshell()->export = env;
	//signal_handler();
	receive_input();
	return (0);
}
