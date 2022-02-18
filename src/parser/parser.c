/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/18 05:26:12 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
static int	parser_build_program(t_info *ms)
{
	t_program	*pgm;

	pgm = new_program();
	if (pgm == NULL)
		return (ERROR);
	ms_program_lstadd_last(&ms->pgmlist, pgm);
	while (ms->tmp_tkn && ms->tmp_tkn->type != PIPE)
	{
		if (ms->tmp_tkn->type == TOKEN)
			ms_program_argv_add(pgm, ms->tmp_tkn->data);
		else if (ms->tmp_tkn->type == REDIR_DGREAT
			|| ms->tmp_tkn->type == REDIR_DLESS
			|| ms->tmp_tkn->type == REDIR_GREAT
			|| ms->tmp_tkn->type == REDIR_LESS)
			if (parser_build_redirection(ms, &pgm) == ERROR)
				return (ERROR);
		ms->tmp_tkn = ms->tmp_tkn->next;
	}
	ms->npgms++;
	return (0);
}

int	parser(t_info *ms)
{
	ms->tmp_tkn = ms->list;
	while (ms->tmp_tkn)
	{
		if (parser_build_program(ms) == ERROR)
			return (ERROR);
		if (ms->tmp_tkn)
			ms->tmp_tkn = ms->tmp_tkn->next;
	}
	return (0);
}
