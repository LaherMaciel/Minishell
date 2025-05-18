/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/16 15:33:331 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mshell	*mshell(void)
{
	static t_mshell	mshell;

	return (&mshell);
}

void	init_shell(char **env)
{
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
	mshell()->env = ft_calloc(sizeof(t_export), 1);
	if (!mshell()->env)
		exit(EXIT_FAILURE);
	mshell()->env = init_env(env);
	if (mshell()->env == NULL)
		handle_error_and_exit(-2, "Failed to create env struct");
	mshell()->expt = ft_calloc(sizeof(t_export), 1);
	if (!mshell()->expt)
		handle_error_and_exit(-2, "Failed to create export struct");
	mshell()->expt = init_export(env);
	mshell()->aux_env = NULL;
	mshell()->expt = export_sorter();
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
	init_shell(env);
	receive_input();
	ft_free_export(NULL);
	ft_free_export(mshell()->env);
	ft_free_array(mshell()->aux_env, 0);
	return (0);
}

/* 
int	main(int argc, char **argv)
{
	char	**result;

	(void) argc;
	ft_printf("input = %s\n", argv[1]);
	result = ft_split_minishell(argv[1]);
	//ft_printf("\n\ninput = %s\n", argv[1]);
	if (!result)
		ft_printf("NULL\n");
	else
		ft_printf("Output:\n%t\n", result);
	ft_free_array(result, ft_arraylen(result));
	return (0);
} */
//ls>>test.txt|cat test.txt|grep "mini lib"
//ls>test.txt | cat test.txt | grep "mini lib"
//"ls | -a > something << dasd 'da sd a sd' fhjsdlf"
//clear && make && valgrind ./minishell "ls | -a > something << dasd 'd as d asd' fhjsdlf"
//ls>>test.txt|cat test.txt|grep "mini lib" ls | -a > something << dasd 'd as d asd' fhjsdlf
