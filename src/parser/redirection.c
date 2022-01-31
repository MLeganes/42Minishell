/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:22:34 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/31 18:21:29 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir *new_redirection(t_info *ms, int is_app, int is_out)
{
	t_redir *new;
	
	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL); // Exit cleaning everything
	new->type = ms->tmp_tkn->type;
	if (ms->tmp_tkn->next && ms->tmp_tkn->next->data)
		new->file = ms->tmp_tkn->next->data; // Next token contain the file.
	else
		printf("Error: Incomplete command, no file.\n");
	new->is_app = is_app;
	new->is_out = is_out;
	new->next = NULL;
	return (new);
}

void ms_redir_lstadd_last(t_program **pgm, t_redir *new)
{
	t_redir *last;

	if ((*pgm)->redir == NULL)
		(*pgm)->redir = new;
	else
	{
		last = (*pgm)->redir;
		while (last->next)
		{
			last = last->next;
		}
		if ( last)
			last->next = new;
	}
}

void parser_build_redirection(t_info *ms, t_program **pgm)
{
	t_redir *redir;
	
	if (ms->tmp_tkn->type == REDIR_GREAT)
	{
		redir = new_redirection(ms, 0, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DGREAT)
	{
		redir = new_redirection(ms, 1, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_LESS)
	{
		redir = new_redirection(ms, 0, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DLESS)
		ms_redir_heredoc(ms, &(*pgm));
	//increment to next, that was where file-name is. 
	ms->tmp_tkn = ms->tmp_tkn->next;
}
