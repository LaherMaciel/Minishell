/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:02:32 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/19 15:55:36 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	high_priority(void)
{
	int	i;
	int	index;
	int	highest;

	i = ft_arraylen(mshell()->input);
	highest = INT_MIN;
	while (i >= 0)
	{
		if (mshell()->input_value[i] >= highest)
		{
			highest = mshell()->input_value[i];
			index = i;
		}
		i--;
	}
	return (index);
}

void	rm_index(int index)
{
	char	**array;

	array = mshell()->input;
	set_inputvalue(index);
	array = ft_rm_from_array(array, ft_arraylen(mshell()->input), index);
	mshell()->input = array;
}

void	rm_indexs(int index1, int index2)
{
	char	**array;
	char	*str;
	int		i;

	array = mshell()->input;
	if (index1 > index2)
	{
		set_inputvalue(index1);
		set_inputvalue(index2);
	}
	else
	{
		set_inputvalue(index2);
		set_inputvalue(index1);
	}
	str = array[index2];
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
	set_inputvalue(index);
	index--;
	while (mshell()->input[++index])
		if (its_what(mshell()->input[index]) == 1
			|| its_what(mshell()->input[index]) == 2)
			aux = ft_append_to_array2(aux, 0, mshell()->input[index], 1);
	if (!aux)
		return (NULL);
	dup_loop(aux);
	return (aux);
}
