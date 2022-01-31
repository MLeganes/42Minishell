/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/31 18:07:52 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_build_program(t_info *ms)
{
	t_program	*pgm;

	// create new program-cmd
	pgm = new_program();
	if ( pgm == NULL)
		return ;
	ms_program_lstadd_last(&ms->pgmlist, pgm);
	while ( ms->tmp_tkn && ms->tmp_tkn->type != PIPE)
	{
		if (ms->tmp_tkn->type == TOKEN)
			ms_program_argv_add(pgm, ms->tmp_tkn->data);	//append
		else if (ms->tmp_tkn->type == REDIR_DGREAT || ms->tmp_tkn->type == REDIR_DLESS 
			|| ms->tmp_tkn->type == REDIR_GREAT || ms->tmp_tkn->type == REDIR_LESS)
			parser_build_redirection(ms, &pgm);
		ms->tmp_tkn = ms->tmp_tkn->next;
	} // END-WHILE
		//if (ms->list && ms->list->type == PIPE)
			//stop. new program
	ms->npgms++;
}

void	parser(t_info *ms)
{
	ms->tmp_tkn = ms->list;
	
	while (ms->tmp_tkn)
	{
		parser_build_program(ms);
		// if (ms->list && ms->list->next)
		// 	free(ms->list->data);
		if (ms->tmp_tkn)
			ms->tmp_tkn = ms->tmp_tkn->next;
	}
	// check what to free!!!
}
