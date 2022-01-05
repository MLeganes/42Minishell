/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:43:41 by amorcill          #+#    #+#             */
/*   Updated: 2021/07/16 10:33:14 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*actual;
	t_list	*next;

	actual = *lst;
	while (actual != NULL)
	{
		next = actual->next;
		del(actual->content);
		free(actual);
		actual = next;
	}
	*lst = NULL;
}
