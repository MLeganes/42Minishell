/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:53:44 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/16 00:16:41 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_case_quote(int chartype, t_info *ms)
{
	if (chartype == CHAR_QUOTE)
		ms->state = STATE_IN_QUOTE;
	else if (chartype == CHAR_DQUOTE)
		ms->state = STATE_IN_DQUOTE;
	ms->tmp_tkn->type = TOKEN;
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
}

// Escape sequence "\"" 
static void	ms_case_escapes(t_info *ms)
{
	ms->tmp_tkn->type = TOKEN;
	ms->idx++;
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->cmdline[ms->idx];
	ms->tmp_tkn->len++;
}

static void	ms_case_general(t_info *ms)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
	ms->tmp_tkn->type = TOKEN;
}

void	ms_case_endtoken(t_info *ms)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = '\0';
	ms->tmp_tkn->next = new_tok(ft_strlen(ms->cmdline) - ms->idx);
	ms->tmp_tkn = ms->tmp_tkn->next;
}

void	ms_state_selector(t_info *ms, int chartype)
{
	if (chartype == CHAR_QUOTE || chartype == CHAR_DQUOTE)
		ms_case_quote(chartype, ms);
	else if (chartype == CHAR_ESCAPESEQUENCE)
		ms_case_escapes(ms);
	else if (chartype == CHAR_GENERAL)
		ms_case_general(ms);
	else if (chartype == CHAR_WHITESPACE || chartype == CHAR_TAB
		|| chartype == CHAR_NEWLINE)
	{
		if (ms->tmp_tkn->len > 0)
			ms_case_endtoken(ms);
	}
	else if (chartype == CHAR_GREATER || chartype == CHAR_LESSER)
		ms_case_redirect(ms, chartype);
	else if (chartype == CHAR_AMPERSAND || chartype == CHAR_PIPE)
	{
		ms_case_multiple(ms, chartype);
	}
}
