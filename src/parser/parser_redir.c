/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:22:34 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/28 20:00:42 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir *new_redirection(t_type type, int is_app, int is_out)
{
	t_redir *new;
	
	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL); // Exit cleaning everything
	new->type = type;
	new->is_app = is_app;
	new->is_out = is_out;
	new->next = NULL;
	return (new);
}

static void ms_redir_lstadd_last(t_info *ms, t_program **pgm, t_redir *new)
{
	t_redir *redir;
	t_redir *redir2;
	
	redir = ms->tmp_pgm->redir;
	redir2 = (*pgm)->redir;
	
	if (redir == NULL)
	{
		redir = new;
	}
	else 
	{
		while (redir != NULL && redir->next != NULL)
		{
			redir = redir->next;
		}
		if (redir)
			redir->next = new;
	}
}

void parser_build_redirection(t_info *ms, t_program **pgm)
{
	t_redir *redir;
	
	if (ms->tmp_tkn->type == REDIR_GREAT)
	{
		redir = new_redirection(REDIR_GREAT, ms->tmp_pgm->next. 0, 1);
		ms_redir_lstadd_last(ms, &(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DGREAT)
	{
		redir = new_redirection(REDIR_DGREAT, 1, 1);
		ms_redir_lstadd_last(ms, &(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_LESS)
	{
		redir = new_redirection(REDIR_LESS, 0, 1);
		ms_redir_lstadd_last(ms, &(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DLESS)
	{
		// Here doc
		
	}
}
