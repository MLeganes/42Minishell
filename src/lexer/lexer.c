/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:31:46 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/11 14:48:48 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/* static int	expand_var(t_info *ms)
{
	char	*var;
	
	ms->cmdline[ms->idx]++;
	var = ft_substr(ms->cmdline, ms->idx, (ft_strlen(ms->cmdline) - ms->idx));
	printf("var %s\n", var);
	return (0);
} */
static int	mini_spliter(t_info *ms)
{
	int	chartype;

	ms->idx = 0;
	ms->list = new_tok(ft_strlen(ms->cmdline));
	ms->tmp_tkn = ms->list;
	while (ms->cmdline[ms->idx] != '\0')
	{
		chartype = ms_chartype(ms->cmdline[ms->idx]);
		ms->tmp_c = ms->cmdline[ms->idx];
/* 		if (ms->state != STATE_GENERAL && chartype == CHAR_VAR)
			expand_var(ms); */
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
		error_exit("error", " unclosed quotes!");
		return (ERROR);
	}
	return (0);
}

int	lexer(t_info *ms)
{
	if (ft_strlen(ms->cmdline))
	{
		if (mini_spliter(ms) != ERROR)
		{
			//print_lexer(ms);
			if (expansion(ms) == -1)
				return (ERROR);
			if (quotes(ms) == -1)
				return ERROR;
			//print_quotes(ms);
		}
		else
			return (ERROR);
	}
	return (0);
}
