/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:02:32 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/23 14:27:09 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	high_priority(void)
{
	int	i;
	int	index;
	int	highest;

	i = -1;
	highest = INT_MIN;
	while (mshell()->input[++i])
	{
		if (mshell()->input_value[i] > highest)
		{
			highest = mshell()->input_value[i];
			index = i;
		}
	}
	return (index);
}

void	rm_index(int index)
{
	int		i;
	int		j;
	int		*quoted;
	char	**array;

	i = -1;
	j = 0;
	array = mshell()->input;
	if (mshell()->input_value)
		free(mshell()->input_value);
	mshell()->input_value = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	quoted = mshell()->quoted;
	mshell()->quoted = ft_calloc(ft_arraylen(mshell()->input) + 1,
		sizeof(int));
	while (mshell()->input[++i])
	{
		if (i != index)
		{
			mshell()->quoted[j] = quoted[i];
			mshell()->input_value[j] = its_what(mshell()->input[i],
				mshell()->quoted[i]);
			j++;
		}
	}
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

static void	dup_loop(char **aux)
{
	int	i;
	int	j;

	i = 0;
	while (aux[i])
	{
		j = -1;
		while (mshell()->input[++j])
		{
			if (ft_strcmp(aux[i], mshell()->input[j]) == 0)
			{
				mshell()->input = ft_rm_from_array(mshell()->input, 0, j);
				break ;
			}
		}
		i++;
	}
}

char	**dupped_arr(int index)
{
	char	**aux;

	aux = NULL;
	if (!mshell()->input || index < 0
		|| index >= (int) ft_arraylen(mshell()->input))
		return (NULL);
	index--;
	while (mshell()->input[++index])
		if (its_what(mshell()->input[index], mshell()->quoted[index]) == 1
			|| its_what(mshell()->input[index], mshell()->quoted[index]) == 2)
			aux = ft_append_to_array2(aux, 0, mshell()->input[index], 1);
	if (!aux)
		return (NULL);
	dup_loop(aux);
	set_inputvalue(index);
	return (aux);
}
