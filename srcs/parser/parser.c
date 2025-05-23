/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/05/23 09:33:37 by lahermaciel      ###   ########.fr       */
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

void	set_inputvalue(void)
{
	int		i;

	i = -1;
	if (mshell()->input_value)
		free(mshell()->input_value);
	mshell()->input_value = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	while (mshell()->input[++i])
		mshell()->input_value[i] = its_what(mshell()->input[i]);
}

void	parser(char *input)
{
	if (!input)
		return ;
	mshell()->input = ft_split_minishell(input);
	if (!mshell()->input)
		return ;
	mshell()->input_value = NULL;
	set_inputvalue();
}

//ls>>test.txt|cat test.txt|grep "mini lib"
//ls>test.txt | cat test.txt | grep "mini lib"
//"ls | -a > something << dasd 'da sd a sd' fhjsdlf"
//clear && make && valgrind ./minishell "ls | -a > something << dasd 'd as d asd' fhjsdlf"
//ls>>test.txt|cat test.txt|grep "mini lib" ls | -a > something << dasd 'd as dasd' fhjsdlf '$USER'=$USER "HOME = $HOME" 'e'ch"o"
//ls>>test.txt | cat test.txt|grep "mini lib" ls|-a>something << dasd 'd as d asd' fhjsdlf
//ls | wc -l
//'e'ch"o" "hello"