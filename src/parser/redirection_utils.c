/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:31:51 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/06 12:32:13 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_redir_lstadd_last(t_program **pgm, t_redir *new)
{
	t_redir	*last;

	if ((*pgm)->redir == NULL)
		(*pgm)->redir = new;
	else
	{
		last = (*pgm)->redir;
		while (last->next)
		{
			last = last->next;
		}
		if (last)
			last->next = new;
	}
}
