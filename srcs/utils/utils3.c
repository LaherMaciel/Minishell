/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:02:32 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/11 11:30:32 by karocha-         ###   ########.fr       */
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
	array = ft_rm_from_array(array, ft_arraylen(mshell()->input), index);
	mshell()->input = array;
	set_inputvalue();
}

void	rm_indexs(int index1, int index2)
{
	char	**array;
	char	*str;
	int		i;

	array = mshell()->input;
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
	set_inputvalue();
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
		if (its_what(mshell()->input[index]) == 1
			|| its_what(mshell()->input[index]) == 2)
			aux = ft_append_to_array2(aux, 0, mshell()->input[index], 1);
	if (!aux)
		return (NULL);
	dup_loop(aux);
	set_inputvalue();
	return (aux);
}
