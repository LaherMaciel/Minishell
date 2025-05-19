/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/05/19 16:55:39 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	about_quotes(char *input, int *quote, size_t i)
{
	if (*quote == 0)
	{
		if (input[i] == '\'')
			*quote = 1;
		if (input[i] == '\"')
			*quote = 2;
	}
	else if ((input[i] == '\'' && *quote == 1)
		|| (input[i] == '\"' && *quote == 2))
		*quote = 0;
}

char	**parser(char *input)
{
	char	**aux;

	if (!input)
		return (NULL);
	aux = ft_split_minishell(input);
	ft_printf("After split:\n\n%t\n\n", aux);
	return (aux);
}
//ls>>test.txt|cat test.txt|grep "mini lib"
//ls>test.txt | cat test.txt | grep "mini lib"
//"ls | -a > something << dasd 'da sd a sd' fhjsdlf"
//clear && make && valgrind ./minishell "ls | -a > something << dasd 'd as d asd' fhjsdlf"
//ls>>test.txt|cat test.txt|grep "mini lib" ls | -a > something << dasd 'd as dasd' fhjsdlf '$USER'=$USER "HOME = $HOME" 'e'ch"o"
//ls>>test.txt | cat test.txt|grep "mini lib" ls|-a>something << dasd 'd as d asd' fhjsdlf
//ls | wc -l
//'e'ch"o" "hello"