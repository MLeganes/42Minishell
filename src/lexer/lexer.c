/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:31:46 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/02 18:02:02 by amorcill         ###   ########.fr       */
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

static int	ms_chartype(char c)
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

static void	ms_case_endtoken(t_info *ms)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = '\0';
	ms->tmp_tkn->next = new_tok(ft_strlen(ms->cmdline) - ms->idx);
	ms->tmp_tkn = ms->tmp_tkn->next;
}

static void	ms_case_redirect(t_info *ms, int chartype)
{
	if (ms->tmp_tkn->len > 0)
		ms_case_endtoken(ms);
	// next token
	ms->tmp_tkn->data[0] = chartype;
	if (ms->cmdline[ms->idx + 1] == chartype)
	{
		ms->tmp_tkn->data[1] = chartype;
		ms->tmp_tkn->data[2] = '\0';
		if (chartype == CHAR_GREATER)
			ms->tmp_tkn->type = REDIR_DGREAT;
		else if (chartype == CHAR_LESSER )
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

static void	ms_case_multiple(t_info *ms, int chartype)
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

static void	ms_state_selector(t_info *ms, int chartype)
{
	if (chartype == CHAR_QUOTE || chartype == CHAR_DQUOTE)
		ms_case_quote(chartype, ms);
	else if (chartype == CHAR_ESCAPESEQUENCE)
		ms_case_escapes(ms);
	else if (chartype == CHAR_GENERAL)
		ms_case_general(ms);
	else if (chartype == CHAR_WHITESPACE)
	{
		if (ms->tmp_tkn->len > 0)
			ms_case_endtoken(ms);
	}
	else if (chartype == CHAR_GREATER || chartype == CHAR_LESSER)
		ms_case_redirect(ms, chartype);
	else if (chartype == CHAR_AMPERSAND || chartype == CHAR_PIPE)
	{		
		// end the token that was being read before
		ms_case_multiple(ms, chartype);
	}
}

static void	ms_state_dquote(t_info *ms, int chartype)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
	if (chartype == CHAR_DQUOTE)
		ms->state = STATE_GENERAL;
}

static void	ms_state_quote(t_info *ms, int chartype)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
	if (chartype == CHAR_QUOTE)
		ms->state = STATE_GENERAL;
}

static void	ms_end_tok(t_info *ms)
{
	if (ms->tmp_tkn->len > 0)
	{
		ms->tmp_tkn->data[ms->tmp_tkn->len] = '\0';
		ms->ntok++;
		ms->tmp_tkn->len = 0;
	}
}

static void	mini_spliter(t_info *ms)
{
	int	chartype;

	ms->idx = 0;
	ms->list = new_tok(ft_strlen(ms->cmdline));
	ms->tmp_tkn = ms->list;
	while (ms->cmdline[ms->idx] != '\0')
	{
		chartype = ms_chartype(ms->cmdline[ms->idx]);
		ms->tmp_c = ms->cmdline[ms->idx];
		if (ms->state == STATE_GENERAL)
			ms_state_selector(ms, chartype);
		else if (ms->state == STATE_IN_DQUOTE)
			ms_state_dquote(ms, chartype);
		else if (ms->state == STATE_IN_QUOTE)
			ms_state_quote(ms, chartype);
		if (chartype == CHAR_NULL)
			ms_end_tok(ms);
		ms->idx++;
	}
	if (ms->cmdline[ms->idx] == '\0' && ms->state != STATE_GENERAL)
	{
		printf("Error: Incomplete command.\n");
		free_after_cmd(ms);
	}
}

void	lexer(t_info *ms)
{
	// like split but puts everything in a linked list 
	//and returns a pointer to the first element
	mini_spliter(ms);
	quotes(ms);
	//print_lexer(ms);
}
