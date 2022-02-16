/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:07:06 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/16 09:59:31 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_delim(char c)
{
	if (c == '=')
		return (true);
	return (false);
}

bool	is_end(char c)
{
	if (c == '\0')
		return (true);
	return (false);
}

t_env	*ms_new_env(char *var, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_env	*env_last(t_env *lst)
{
	while (lst != NULL && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	env_addback(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = env_last(*lst);
	last->next = new;
	new->next = NULL;
}

t_env	*ms_find_env_var(t_info *ms, char **var)
{
	ms->tmp_env = ms->env_v;
	while (ms->tmp_env != NULL)
	{
		if (ft_strncmp((*var), ms->tmp_env->var, ft_strlen((*var))) == 0)
		{
			return (ms->tmp_env);
		}
		ms->tmp_env = ms->tmp_env->next;
	}
	return (NULL);
}

void	get_env(t_info *ms)
{
	int			i;
	int			j;
	extern char	**environ;

	ms->env = environ;
	i = 0;
	ms->env_v = NULL;
	ms->tmp_env = NULL;
	while (environ[i])
	{
		j = 0;
		while (is_var_delim(environ[i][j]) == false &&
				is_end(environ[i][j]) == false)
			j++;
		ms->tmp_env = ms_new_env(ft_substr(environ[i], 0, j),
				ft_substr(environ[i], j + 1, ft_strlen(environ[i]) - j - 1));
		env_addback(&ms->env_v, ms->tmp_env);
		i++;
	}
}
