/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:57 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/15 14:36:10 by arohmann         ###   ########.fr       */
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
		error_exit("error", " No such file or directory");
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (cwd)
		free(cwd);
}
