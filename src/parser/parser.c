/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/06 12:22:11 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// create new program-cmd
		// END-WHILE
		//if (ms->list && ms->list->type == PIPE)
			//stop. new program after while
static void	parser_build_program(t_info *ms)
{
	t_program	*pgm;

	pgm = new_program();
	if (pgm == NULL)
		return ;
	ms_program_lstadd_last(&ms->pgmlist, pgm);
	while (ms->tmp_tkn && ms->tmp_tkn->type != PIPE)
	{
		if (ms->tmp_tkn->type == TOKEN)
			ms_program_argv_add(pgm, ms->tmp_tkn->data);
		else if (ms->tmp_tkn->type == REDIR_DGREAT
			|| ms->tmp_tkn->type == REDIR_DLESS
			|| ms->tmp_tkn->type == REDIR_GREAT
			|| ms->tmp_tkn->type == REDIR_LESS)
			parser_build_redirection(ms, &pgm);
		ms->tmp_tkn = ms->tmp_tkn->next;
	}
	ms->npgms++;
}

		// if (ms->list && ms->list->next)
		// 	free(ms->list->data); after parser_built
void	parser(t_info *ms)
{
	ms->tmp_tkn = ms->list;
	while (ms->tmp_tkn)
	{
		parser_build_program(ms);
		if (ms->tmp_tkn)
			ms->tmp_tkn = ms->tmp_tkn->next;
	}
}
	// check what to free!!!
