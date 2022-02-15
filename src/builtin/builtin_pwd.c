/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:57 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/15 19:49:00 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	exec_pwd(t_info *ms, t_program *pgm)
{
	char	*cwd;

	(void)ms;
	(void)pgm;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("Minishel: pwd");
		g_exit_status = 2;
	}
	else{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_exit_status = 0;
	}
	if (cwd)
		free(cwd);
}
