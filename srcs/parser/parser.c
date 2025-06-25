/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:31 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/25 15:35:23 by lahermaciel      ###   ########.fr       */
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
	int		j;
	int		*quoted;

	i = -1;
	if (mshell()->input_v)
		free(mshell()->input_v);
	mshell()->input_v = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	quoted = mshell()->quoted;
	mshell()->quoted = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	j = 0;
	while (++i < (int) ft_arraylen(mshell()->input) + 1)
	{
		if (i != index)
		{
			mshell()->quoted[j] = quoted[i];
			mshell()->input_v[j] = its_what(j);
			j++;
		}
	}
	if (quoted)
		free(quoted);
}

void	set_inputvalues(int index1, int index2)
{
	int	i;
	int	j;
	int	*quoted;

	if (mshell()->input_v)
		free(mshell()->input_v);
	mshell()->input_v = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	quoted = mshell()->quoted;
	mshell()->quoted = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	j = 0;
	i = -1;
	while (++i < (int) ft_arraylen(mshell()->input) + 1)
	{
		if (i != index1 && i != index2)
		{
			mshell()->quoted[j] = quoted[i];
			mshell()->input_v[j] = its_what(i);
			j++;
		}
	}
	if (quoted)
		free(quoted);
}

void	parser(char *input)
{
	if (!input)
		return ;
	ft_split_shell_lst(input);
	if (!mshell()->input)
		mshell()->exit_status = 1;
	if (!mshell()->input_v)
		mshell()->exit_status = 1;
	mshell()->exit_status = 0;
	free(input);
}
