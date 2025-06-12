/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/12 14:47:12 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo hello > test | echo world > test2 | cat test
//echo hello > test | cat test | echo world > test2 | cat test2
void	piper(char **aux)
{
	pid_t	pid;
	int		pipefd[2];
	int		i;

	i = 0;
	if (pipe(pipefd) < 0)
	{
		perror("Minishell: pipe");
		mshell()->exit_status = 1;
		return ;
	}
	ft_printf("\npipe args:\n%tinfile = %i, outfile = %i\n\n", aux,
		mshell()->infile, mshell()->outfile);
	pid = create_child_process();
	purgatory(pid, pipefd, i, aux);
}

void	exit_status(char *line)
{
	if (line)
		ft_fdprintf(mshell()->outfile, "%i%s: command not found\n",
			mshell()->exit_status, line + 2);
	else
		ft_fdprintf(mshell()->outfile, "%i: command not found\n",
			mshell()->exit_status);
}

int	handle_special(int index)
{
	char	**aux;

	if (ft_strcmp(mshell()->input[index], "|") == 0)
	{
		aux = pipe_dupped_arr(index);
		if (!aux || !aux[0])
		{
			mshell()->exit_status = 2;
			return (1);
		}
		piper(aux);
		ft_free_array(aux, 0);
	}
	return (0);
}

static void	clear_input(char **aux)
{
	int	i;
	int	j;

	i = -1;
	while (aux[++i])
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
	}
	set_inputvalue();
}

char	**pipe_dupped_arr(int index)
{
	char	**aux;
	int		i;

	aux = NULL;
	if (index <= 0)
	{
		ft_fdprintf(mshell()->outfile, "Minishell: "
			"syntax error near unexpected token `|'\n");
		return (NULL);
	}
	if (!mshell()->input || index >= (int) ft_arraylen(mshell()->input))
		return (NULL);
	rm_index(index);
	i = -1;
	while (++i < index)
		if (its_what(mshell()->input[i]) == 1
			|| its_what(mshell()->input[i]) == 2)
			aux = ft_append_to_array2(aux, 0, mshell()->input[i], 1);
	if (!aux)
		return (NULL);
	clear_input(aux);
	return (aux);
}
