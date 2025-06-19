/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/19 16:18:58 by lawences         ###   ########.fr       */
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

void	set_inputvalue(int index)
{
	int		i;
	int		*new_array;

	i = -1;
	new_array = mshell()->input_value;
	mshell()->input_value = ft_calloc(ft_arraylen(mshell()->input),
		sizeof(int));
	if (new_array)
	{
		while (new_array[++i])
		{

			if (new_array[i] != index)
				mshell()->input_value[i] = new_array[i];
		}
		free(new_array);
	}
	else
	{
		while (mshell()->input[++i])
			mshell()->input_value[i] = its_what(mshell()->input[i]);
	}
}

void	parser(char *input)
{
	if (!input)
		return ;
	ft_split_minishell_lst(input);
	if (!mshell()->input)
		mshell()->exit_status = 1;
	if (!mshell()->input_value)
		mshell()->exit_status = 1;
	mshell()->exit_status = 0;
	free(input);
}
