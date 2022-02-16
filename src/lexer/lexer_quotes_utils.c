/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:58:31 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/16 14:55:08 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_expansion(t_info *ms, char **copy, char **var, char **tmp)
{
	ms->tmp_env = ms_find_env_var(ms, var);
	if (ms->tmp_env == NULL)
	{
		free_str(*var);
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	(*tmp) = ft_strjoin(*copy, ms->tmp_env->content);
	free_str(*copy);
	return (0);
}

static void	expand_exit_s(char **tmp, char *copy)
{
	char	*nbr;

	nbr = ft_itoa(g_exit_status);
	(*tmp) = ft_strjoin(copy, nbr);
	free_str(nbr);
	free_str(copy);
}

int	ms_exp_var(t_info *ms, char **tmp, char *str, int *i)
{
	char	*var;
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
		expand_exit_s(tmp, copy);
	else
	{
		if (do_expansion(ms, &copy, &var, tmp) == ERROR)
			return (ERROR);
	}
	free_str(var);
	return (k);
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

char	*ms_error_return(char *tmp, char *str, int *err, int b)
{
	if (b == 1)
		*err = -1;
	free_str(tmp);
	free_str(str);
	return (NULL);
}
