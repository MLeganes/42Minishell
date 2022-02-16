/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:41:33 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/16 15:51:03 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = ms_new_env(var, content);
	env_addback(&env, tmp);
}

static void	ms_var_handler(t_info *ms, char **args, int len, int i)
{
	if (ms->tmp_env->content != NULL)
		free(ms->tmp_env->content);
	ms->tmp_env->content = ft_substr(args[i], (len + 1),
			(ft_strlen(args[i]) - len));
}

static int	arg_error(char *args)
{
	error_exit(args, " is not a valid identifier");
	return (0);
}

/*
** checks if args are valid, if not error is printed
*/
static int	ms_insert_var(t_info *ms, t_env *env, char **args)
{
	int		i;
	int		len;
	int		ret;
	char	*var;

	i = 1;
	ret = 0;
	len = 0;
	while (args[i])
	{
		if (args[i][0] == '=')
			return (arg_error(args[i]));
		len = ms_check_var(args[i]);
		var = ft_substr(args[i], 0, len);
		ms->tmp_env = ms_find_env_var(ms, &var);
		if (args[i][len] != '=' || args[i][0] == '?' || len <= 0)
			ret = 1;
		else if (ms->tmp_env == NULL)
			ms_add_new_var(env, args[i]);
		else
			ms_var_handler(ms, args, len, i);
		free_str(var);
		i++;
	}
	return (ret);
}

/*
** if export is called with args they are added, else vars are printed
*/
int	exec_export(t_info *ms, t_program *pgm)
{
	ms->tmp_env = ms->env_v;
	if (pgm->argv[1] != NULL)
	{
		if (ms_insert_var(ms, ms->tmp_env, pgm->argv) == 1)
			return (ERROR);
	}
	else
		export_print(ms, ms->env_v);
	return (0);
}
