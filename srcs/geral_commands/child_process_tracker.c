/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_tracker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:37:12 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/26 13:44:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_child_pid(pid_t pid)
{
	t_child_pid	*new_pid;
	t_child_pid	*current;

	new_pid = malloc(sizeof(t_child_pid));
	if (!new_pid)
	{
		perror("minishell: malloc");
		return ;
	}
	new_pid->pid = pid;
	new_pid->next = NULL;
	if (!mshell()->child_pids)
		mshell()->child_pids = new_pid;
	else
	{
		current = mshell()->child_pids;
		while (current->next)
			current = current->next;
		current->next = new_pid;
	}
	mshell()->num_children++;
}

void	free_child_pids(void)
{
	t_child_pid	*current;
	t_child_pid	*next;

	current = mshell()->child_pids;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	mshell()->child_pids = NULL;
	mshell()->num_children = 0;
}
