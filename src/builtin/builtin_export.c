/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:41:33 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/09 12:28:23 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** returns length, if first char is a number returns 0, if it is ? returns 1
*/
int	ms_check_var(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[0]) == 1)
		return (0);
	if (var[i] == '?')
		return (1);
	while (ft_isalnum(var[i]) || (var[i] == '_'))
		i++;
	return (i);
}

/*
** extracts the var name and content and adds it at the end of env
*/
void	ms_add_new_var(t_env *env, char *arg)
{
	int		i;
	char	*var;
	char	*content;
	t_env	*tmp;

	i = 0;
	while (arg[i] != '=')
		i++;
	var = ft_substr(arg, 0, i);
	content = ft_substr(arg, i + 1, ft_strlen(arg));
	tmp = ms_new_env(var, content, NULL);
	while (env != NULL && env->next != NULL)
	{
		env = env->next;
	}
	env->next = tmp;
}

/*
** checks if args are valid, if not error is printed
*/
static int	ms_insert_var(t_env *env, char **args)
{
	int	i;
	int	len;
	int	ret;

	i = 1;
	ret = 0;
	len = 0;
	while (args[i])
	{
		if (args[i][0] == '=')
		{
			error_exit(args[i], " is not a valid identifier");
			break;
		}
		len = ms_check_var(args[i]);
		if (args[i][len] != '=' || args[i][0] == '?' || len <= 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(" is not a valid identifier\n", 2);
			//error_exit(args[i], " is not a valid identifier\n");
			ret = 1;
		}
		else
			ms_add_new_var(env, args[i]);
		i++;
	}
	return (ret);
}

/*
** if export is called with args they are added, else vars are printed
*/
void	exec_export(t_info *ms, t_program *pgm)
{
	ms->tmp_env = ms->env_v;
	if (pgm->argv[1] != NULL)
		ms_insert_var(ms->tmp_env, pgm->argv);
	else
		export_print(ms->env_v);
	return ;
}
