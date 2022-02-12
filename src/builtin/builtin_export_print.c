/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:47:36 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/12 20:29:34 by arohmann         ###   ########.fr       */
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
	free(s1);
	s1 = ft_strjoin(s2, "\"");
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

	arr = (char **)malloc(sizeof(char *) * ms_lstlen(env) + 1);
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
** sorts a 2D array according to ascii values
*/
void	ms_sort_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		j = 0;
		while (tab[j + 1])
		{
			if (ft_strcmp(tab[j], tab[i]) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[i];
				tab[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

/*
** calls sorting function and prints all vars
*/
void	export_print(t_env *env)
{
	char	**envp;
	int		i;

	envp = ms_env_to_arr(env);
	i = 0;
	ms_sort_tab(envp);
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
	return ;
}
