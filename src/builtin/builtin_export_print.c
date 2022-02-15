/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:47:36 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/15 23:08:35 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_lstlen(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*ms_join_export(t_env *data)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(data->var, "=\"");
	s2 = ft_strjoin(s1, data->content);
	if (s1)
		free(s1);
	s1 = ft_strjoin(s2, "\"");
	if (s2)
		free(s2);
	return (s1);
}

/*
** puts all env_vars in a 2D array
*/
char	**ms_env_to_arr(t_env *env)
{
	int		i;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (ms_lstlen(env) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		if (env->content)
			arr[i] = ms_join_export(env);
		else
			arr[i] = ft_strdup(env->var);
		i++;
		env = env->next;
	}
	arr[i] = 0;
	return (arr);
}

/*
** calls sorting function and prints all vars
*/
void	export_print(t_info *ms, t_env *env)
{
	(void)ms;
	while (env != NULL)
	{
		printf("declare -x %s", env->var);
		printf("=");
		printf("%s\n", env->content);
		env = env->next;
		g_exit_status = 0;
	}
	return ;
}
