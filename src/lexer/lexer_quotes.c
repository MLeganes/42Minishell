/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:43:32 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/15 19:39:24 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_quotes(char **tmp, char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\'')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	(*i)++;
	while (str[(*i)] != '\0')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	if (str[(*i)] == '\0')
		(*tmp) = ms_append_char((*tmp), '\0');
	return (0);
}

static int	ms_dq_no_exp(char **tmp, char *str, int *i)
{
	if (str[(*i)] == '\"')
		(*i)++;
	while (str[(*i)] != '\0')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	if (str[(*i)] == '\0')
		(*tmp) = ms_append_char((*tmp), '\0');
	return (0);
}

static int	ms_d_quotes(t_info *ms, char **tmp, char *str, int *i)
{
	int	k;

	k = 0;
	while (str[(*i)] != '\"' && str[(*i)] != '\0' && str[(*i)] != '$')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	if (str[(*i)] == '$')
	{
		k = ms_exp_var(ms, tmp, str, i);
		if (k == -1)
			return (-1);
		(*i) += k;
	}
	else
		ms_dq_no_exp(tmp, str, i);
	return (0);
}

static char	*ms_del_quotes(t_info *ms, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			ms_quotes(&tmp, str, &i);
		else if (str[i] == '\"')
		{
			i++;
			if (ms_d_quotes(ms, &tmp, str, &i) == -1)
			{
				if (tmp)
					free(tmp);
				if (str)
					free(str);
				return (NULL);
			}
		}
		else
		{
			tmp = ms_append_char(tmp, str[i]);
			i++;
		}
	}
	if (tmp != NULL)
		ms_end_tmp(&tmp, &i);
	if (str != NULL)
		free(str);
	return (tmp);
}

int	quotes(t_info *ms)
{
	ms->tmp_tkn = ms->list;
	while (ms->tmp_tkn != NULL)
	{
		ms->tmp_tkn->data = ms_del_quotes(ms, ms->tmp_tkn->data);
		if (ms->tmp_tkn->data == NULL)
		{
			error_exit(" error", " variable not found");
			return (-1);
		}
		ms->tmp_tkn = ms->tmp_tkn->next;
	}
	return (0);
}
