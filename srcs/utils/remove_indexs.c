/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:02:32 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/19 20:11:09 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	aux_rm_idex(int index, int *quoted)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (mshell()->input[++i])
	{
		if (i != index)
		{
			mshell()->quoted[j] = quoted[i];
			mshell()->input_v[j] = its_what(i);
			j++;
		}
	}
}

void	rm_index(int index)
{
	int		*quoted;
	char	**array;

	array = mshell()->input;
	if (mshell()->input_v)
		free(mshell()->input_v);
	mshell()->input_v = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	quoted = mshell()->quoted;
	mshell()->quoted = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	aux_rm_idex(index, quoted);
	if (quoted)
		free(quoted);
	array = ft_rm_from_array(array, ft_arraylen(mshell()->input), index);
	mshell()->input = array;
}

void	rm_indexs(int index1, int index2)
{
	char	**array;
	char	*str;
	int		i;

	array = mshell()->input;
	str = array[index2];
	set_inputvalues(index1, index2);
	array = ft_rm_from_array(array, ft_arraylen(array), index1);
	i = -1;
	while (array[++i])
	{
		if (ft_strcmp(str, array[i]) == 0)
		{
			array = ft_rm_from_array(array, ft_arraylen(array), i);
			break ;
		}
	}
	mshell()->input = array;
}
