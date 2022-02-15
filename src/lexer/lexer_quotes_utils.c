/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:58:31 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/16 00:17:10 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exp_var(t_info *ms, char **tmp, char *str, int *i)
{
	char	*var;
	char	*nbr;
	char	*copy;
	int		k;

	k = 0;
	var = NULL;
	while (str[(*i) + k] != '\"' && str[(*i) + k] != '\0'
		&& str[(*i) + k] != ' ' && str[(*i) + k] != '/')
		k++;
	if (str[(*i) + k] != '\0')
		(*tmp) = ms_append_char((*tmp), '\0');
	var = ft_substr(str, (*i) + 1, (k - 1));
	copy = *tmp;
	if (ft_strcmp(var, "?") == 0)
	{
		nbr = ft_itoa(g_exit_status);
		(*tmp) = ft_strjoin(copy, nbr);
		if (nbr)
			free(nbr);
		if (copy)
			free(copy);
	}
	else
	{
		copy = *tmp;
		ms->tmp_env = ms_find_env_var(ms, &var);
		if (ms->tmp_env == NULL)
		{
			if (var)
				free(var);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
		(*tmp) = ft_strjoin(copy, ms->tmp_env->content);
		if (copy)
			free(copy);
	}
	if (var)
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
	if (str)
		free(str);
	return (tmp);
}
