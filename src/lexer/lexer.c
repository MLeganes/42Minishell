/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:31:46 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/17 14:58:10 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_exp_var(t_info *ms)
{
	int		len;
	int		start;
	char	*var;

	len = 0;
	var = NULL;
	ms->idx++;
	start = ms->idx;
	while (ms->cmdline[ms->idx] != '\'' && ms->cmdline[ms->idx] != '\"'
		&& ms->cmdline[ms->idx] != ' ' && ms->cmdline[ms->idx] != '/'
		&& ms->cmdline[ms->idx] != '$' && ms->cmdline[ms->idx] != '\0')
	{
		ms->idx++;
		len++;
	}
	if (ms->cmdline[ms->idx] == '$' && ms->cmdline[ms->idx] == '\"' && ms->cmdline[ms->idx] != '\'')
		ms->idx--;
	var = ft_substr(ms->cmdline, start, len);
	return (var);
}

static void	expand(t_info *ms)
{
	char	*var;

	var = get_exp_var(ms);
	if (var)
		printf("var: %s\n", var);

	free_str(var);
}

static void	ms_state_dquote(t_info *ms, int chartype)
{
	if (chartype == CHAR_DQUOTE)
		ms->idx++;
	if (ms_chartype(ms->cmdline[ms->idx]) != CHAR_VAR)
	{
		ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->cmdline[ms->idx];
		ms->tmp_tkn->len++;
		ms->tmp_tkn->in_dq = 1;
	}
	else
		expand(ms);
	if ((chartype == CHAR_DQUOTE) || (ms_chartype(ms->cmdline[ms->idx]) == CHAR_DQUOTE))
		ms->state = STATE_GENERAL;
}

static void	ms_state_quote(t_info *ms, int chartype)
{
	if (chartype == CHAR_QUOTE)
		ms->idx++;
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->cmdline[ms->idx];
	ms->tmp_tkn->len++;
	ms->tmp_tkn->in_q = 1;
	if (chartype == CHAR_QUOTE)
	{
		ms->state = STATE_GENERAL;
		printf("tok: %i\n", ms->tmp_tkn->in_q);
		printf("tokd: %i\n", ms->tmp_tkn->in_dq);
	}
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
		add_history(ms->cmdline);
		if (mini_spliter(ms) != ERROR)
		{
/* 			if (expansion(ms) == -1)
				return (ERROR);
			if (quotes(ms) == -1)
				return (ERROR); */
		}
		else
			return (ERROR);
	}
	return (0);
}
