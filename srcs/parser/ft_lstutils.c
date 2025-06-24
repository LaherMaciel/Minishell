/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:43:04 by lawences          #+#    #+#             */
/*   Updated: 2025/06/24 19:44:59 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Calculates the number of elements in a linked list.
 *
 * This function counts the number of elements in the linked list pointed to by
 * 'lst'. It iterates through the list and increments a counter for each element
 * encountered.
 *
 * @param lst The first element of the linked list.
 * @return The number of elements in the linked list.
 */
int	ft_lstsize_shell(t_pars_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/**
 * @brief Finds the last element of a linked list.
 *
 * This function traverses the linked list pointed to by 'lst' and returns a
 * pointer to the last element. If the input list is empty (NULL), the function
 * returns NULL.
 *
 * @param lst The first element of the linked list.
 * @return A pointer to the last element of the linked list, or NULL if the list
 * is empty.
 */
t_pars_lst	*ft_lstlast_shell(t_pars_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @brief Adds a new element to the end of a linked list.
 *
 * This function adds the given 'new' element to the end of the linked list
 * pointed to by 'lst'. If the 'lst' pointer is NULL, the 'lst' pointer will be
 * updated to point to the 'new' element.
 *
 * @param lst A pointer to a pointer to the first element of the linked list.
 * @param new The element to be added to the end of the linked list.
 */
void	ft_lstadd_back_shell(t_pars_lst **lst, t_pars_lst *new)
{
	t_pars_lst	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast_shell(*lst);
	temp->next = new;
}

/**
 * @brief Creates a new element for a linked list.
 *
 * This function creates a new element for a linked list with the provided
 * 'content'. The 'content' pointer is assigned to the element's content, and
 * the 'next' pointer is set to NULL.
 *
 * @param content The content to be assigned to the new element.
 * @return A pointer to the newly created element, or NULL if memory allocation
 * fails.
 */
t_pars_lst	*ft_lstnew_shell(void *content, int quoted)
{
	t_pars_lst	*new_list;

	new_list = malloc(sizeof(t_pars_lst));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->quoted = quoted;
	new_list->next = NULL;
	return (new_list);
}
