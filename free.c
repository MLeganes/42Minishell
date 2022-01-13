/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:21:55 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/13 12:03:50 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_list(t_info *ms)
{
	t_token *actual;
	t_token *next;
	
	if (ms->list != NULL)
	{
		actual = ms->list;
		while ( actual != NULL)
		{
			next = actual->next;
			if (actual->data)
				free(actual->data);
			if (actual->expansion)
				free(actual->expansion);
			if (actual->next != NULL)
			 	free(actual);
			actual = next;
		}		
		ms->list = NULL;
	}
}

void free_after_cmd(t_info *ms)
{
	if (ms->cmdline != NULL)
		free(ms->cmdline);
	free_list(ms);
	if (ms->tmp_tkn != NULL)
	{		
		free(ms->tmp_tkn);
		ms->tmp_tkn = NULL;
	}
}
