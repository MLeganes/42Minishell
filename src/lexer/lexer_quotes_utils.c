/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:58:31 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/20 21:21:58 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_expansion(t_info *ms, char *copy, char *var, char **tmp)
{
	ms->tmp_env = ms_find_env_var(ms, &var);
	if (ms->tmp_env == NULL)
	{
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	(*tmp) = ft_strjoin(copy, ms->tmp_env->content);
	if (copy)
		free_str(copy);
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

static int	loop_var(t_info *ms, char **tmp, char **var)
{
	char	*copy;
	int		j;

	j = 0;
	while (var[j])
	{
		copy = *tmp;
		if (ft_strcmp(var[j], "?") == 0)
			expand_exit_s(tmp, copy);
		else
		{
			if (do_expansion(ms, copy, var[j], tmp) == ERROR)
			{
				free_argv(var);
				return (ERROR);
			}
		}
		j++;
	}
	return (0);
}

int	ms_exp_var(t_info *ms, char **tmp, char *str, int *i)
{
	char	*s;
	char	**var;
	int		k;

	k = 0;
	var = NULL;
	ms->idx = 0;
	while (str[(*i) + k] != '\"' && str[(*i) + k] != '\0'
		&& str[(*i) + k] != '\''
		&& str[(*i) + k] != ' ' && str[(*i) + k] != '/')
		k++;
	if (str[(*i) + k] != '\0')
		(*tmp) = ms_append_char((*tmp), '\0');
	s = ft_substr(str, (*i) + 1, (k - 1));
	var = ft_split(s, '$');
	if (loop_var(ms, tmp, var) == ERROR)
		return (ERROR);
	free_str(s);
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
