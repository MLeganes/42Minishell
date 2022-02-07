/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:32:06 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/06 13:36:31 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_tok(int len)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->data = ft_calloc(sizeof(char), len + 1);
	if (new->data == NULL)
		return (NULL);
	new->type = NONE;
	new->expansion = NULL;
	new->next = NULL;
	new->len = 0;
	new->cmdname = CMD_NO_FOUND;
	return (new);
}

t_token	*toklast(t_token *tok)
{
	while (tok != NULL && tok->next != NULL)
	{
		tok = tok->next;
	}
	return (tok);
}

int	ms_chartype(char c)
{
	if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == '\0')
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

void	ms_case_multiple(t_info *ms, int chartype)
{
	if (ms->tmp_tkn->len > 0)
		ms_case_endtoken(ms);
	ms->tmp_tkn->data[0] = chartype;
	ms->tmp_tkn->data[1] = '\0';
	if (chartype == CHAR_AMPERSAND)
		ms->tmp_tkn->type = AMPERSAND;
	else if (chartype == CHAR_PIPE)
	{
		ms->tmp_tkn->type = PIPE;
		ms->npipes++;
	}
	ms->tmp_tkn->next = new_tok(ft_strlen(ms->cmdline) - ms->idx);
	ms->tmp_tkn = ms->tmp_tkn->next;
}

void	ms_case_redirect(t_info *ms, int chartype)
{
	if (ms->tmp_tkn->len > 0)
		ms_case_endtoken(ms);
	ms->tmp_tkn->data[0] = chartype;
	if (ms->cmdline[ms->idx + 1] == chartype)
	{
		ms->tmp_tkn->data[1] = chartype;
		ms->tmp_tkn->data[2] = '\0';
		if (chartype == CHAR_GREATER)
			ms->tmp_tkn->type = REDIR_DGREAT;
		else if (chartype == CHAR_LESSER)
			ms->tmp_tkn->type = REDIR_DLESS;
		ms->idx++;
	}
	else
	{
		ms->tmp_tkn->data[1] = '\0';
		if (chartype == CHAR_GREATER)
			ms->tmp_tkn->type = REDIR_GREAT;
		else if (chartype == CHAR_LESSER)
			ms->tmp_tkn->type = REDIR_LESS;
	}	
	ms->tmp_tkn->next = new_tok(ft_strlen(ms->cmdline) - ms->idx);
	ms->tmp_tkn = ms->tmp_tkn->next;
}
