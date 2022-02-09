/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:58:31 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/09 15:27:11 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exp_var(t_info *ms, char **tmp, char *str, int *i)
{
	char	*var;
	int		k;

	k = 0;
	var = NULL;
	while (str[(*i) + k] != '\"' && str[(*i) + k] != '\0'/*  && str[(*i) + k] != ' ' */) 
		k++;
/* 	if (str[(*i) + k] == ' ')
		printf("hi\n"); */
	if (str[(*i) + k] != '\0')
		(*tmp) = ms_append_char((*tmp), '\0');
	var = ft_substr(str, (*i) + 1, (k - 1));
	if (ft_strcmp(var, "?") == 0)
		(*tmp) = ft_strjoin((*tmp), ft_itoa(g_exit_status));
	else
	{
	ms->tmp_env = ms_find_env_var(ms, &var);
	if (ms->tmp_env == NULL)
	{
		free(var);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	(*tmp) = ft_strjoin((*tmp), ms->tmp_env->content);
	}
	free(var);
	return (k);
}

void	ms_end_tmp(char **tmp, int *i)
{
	(*i) = ft_strlen(*tmp);
	(*tmp)[(*i)] = '\0';
}

char	*ms_append_char(char *str, char c)
{
	char	*tmp;

	if (str == NULL)
	{
		tmp = ft_calloc(sizeof(char), 2);
		tmp[0] = c;
		return (tmp);
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (tmp == NULL)
		return (NULL);
	ft_memcpy(tmp, str, ft_strlen(str) + 1);
	tmp[ft_strlen(str)] = c;
	free(str);
	return (tmp);
}
