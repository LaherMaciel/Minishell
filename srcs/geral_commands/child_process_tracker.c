/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_tracker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:37:12 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 11:56:06 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Create a child process using fork().
 *
 * This function forks the current process and returns the child's PID. If fork
 * fails, it exits with an error message.
 *
 * @return int - The PID of the child process.
 */
int	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mshell()->exit_status = 1;
		handle_error_and_exit(-1, "Fork failed");
	}
	return (pid);
}

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

void	wait_for_childs(void)
{
	t_child_pid	*current;
	int			status;

	current = mshell()->child_pids;
	status = 0;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			mshell()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mshell()->exit_status = 128 + WTERMSIG(status);
		current = current->next;
		mshell()->num_children--;
	}
}
