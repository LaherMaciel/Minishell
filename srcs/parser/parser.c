/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/16 20:35:16 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	about_quotes(char *input, t_parsing *counts)
{
	if (counts->quote == 0)
	{
		if (input[counts->i] == '\'')
			counts->quote = 1;
		if (input[counts->i] == '\"')
			counts->quote = 2;
	}
	else if ((input[counts->i] == '\'' && counts->quote == 1)
		|| (input[counts->i] == '\"' && counts->quote == 2))
		counts->quote = 0;
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
	//mshell()->input = ft_split_minishell_lst(input);
	mshell()->input = ft_split_minishell(input);
	if (!mshell()->input)
		return ;
	mshell()->input_value = NULL;
	set_inputvalue();
	mshell()->exit_status = 0;
	free(input);
}
