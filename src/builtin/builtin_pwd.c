/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:57 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/05 22:34:27 by annarohmnn       ###   ########.fr       */
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
		printf("minishel: No such file or directory\n");
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
}
