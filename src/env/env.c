/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:07:06 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/09 14:45:23 by arohmann         ###   ########.fr       */
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

t_env	*ms_new_env(char *var, char *content, t_env *next)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->content = content;
	new->next = next;
	return (new);
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

void	get_env(t_info *ms, char **env)
{
	int	i;
	int	j;

	i = 0;
	ms->env_v = NULL;
	ms->tmp_env = ms->env_v;
	ms->env_ptr_copy = env;
	while (env[i])
	{
		j = 0;
		while (is_var_delim(env[i][j]) == false && is_end(env[i][j]) == false)
			j++;
		ms->tmp_env = ms_new_env(ft_substr(env[i], 0, j),
				ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1),
				ms->tmp_env);
		i++;
	}
	//ms->tmp_env = ms_new_env("?", ft_itoa(g_exit_status), ms->tmp_env);
	ms->env_v = ms->tmp_env;
}
