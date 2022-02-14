/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:57 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/13 21:05:01 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	exec_pwd(t_info *ms, t_program *pgm)
{
	char	*cwd;
	char	*p;
	t_env	*pwd;

	(void)ms;
	(void)pgm;
	p = ft_strdup("PWD");
	cwd = getcwd(NULL, 0);
	pwd = ms_find_env_var(ms, &p);
	free(pwd->content);
	if (pwd != NULL)
		pwd->content = cwd;
	if (cwd == NULL)
		error_exit("error", " No such file or directory");
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (cwd)
		free(cwd);
	free(p);
}
