/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <lwencesl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:38:53 by lwencesl          #+#    #+#             */
/*   Updated: 2023/06/22 15:38:21 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Deletes a single element from a linked list.
 *
 * This function deletes the given list element 'lst' by freeing the memory
 * allocated for its content using the provided 'del' function and then
 * deallocating the memory for the element itself.
 *
 * @param lst The element to be deleted.
 * @param del A function pointer that takes a pointer to an element's content
 * and frees its memory.
 */
void	ft_lstdelone_shell(t_pars_lst *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/**
 * @brief Clears a linked list and frees its memory.
 *
 * This function clears the linked list pointed to by 'lst' by deallocating
 * memory for each element and its associated content using the provided 'del'
 * function. The 'del' function should be capable of freeing the memory of a
 * single list element. After clearing the list, the 'lst' pointer is set to
 * NULL.
 *
 * @param lst A pointer to a pointer to the first element of the linked list.
 * @param del A function pointer that takes a pointer to an element's content
 * and frees its memory.
 */
void	ft_lstclear_shell(t_pars_lst **lst, void (*del)(void*))
{
	t_pars_lst	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone_shell(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

void	list_to_mshell(t_pars_lst *lst)
{
	t_pars_lst	*head;
	size_t		i;
	size_t		len;

	head = lst;
	len = ft_lstsize_shell(lst);
	mshell()->input = ft_calloc(len + 1, sizeof(char *));
	if (!mshell()->input)
		return ;
	mshell()->input_value = ft_calloc(len + 1, sizeof(int));
	if (!mshell()->input_value)
		return ;
	i = 0;
	while (lst)
	{
		mshell()->input[i] = ft_strdup(lst->content);
		if (is_builtin(mshell()->input[i]))
			mshell()->input_value[i++] = 2;
		else
			mshell()->input_value[i++] = lst->value;
		lst = lst->next;
	}
	ft_lstclear_shell(&head, free);
}
