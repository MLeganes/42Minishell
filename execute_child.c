/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/21 17:47:14 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_child(t_info *ms, int fd[2], int old_fd[2])
{
	
	if (ms->tmp_pgm->next)
	{ // if pipe, redirection
		close(fd[READ]);
		dup2(fd[WRITE], STDIN_FILENO);
		close(fd[WRITE]);
	}
	if (old_fd[WRITE] != -1)
	{  // no pipe, std out.
		close(old_fd[WRITE]);
		dup2(old_fd[READ], STDIN_FILENO);
		close(old_fd[READ]);
	}
	
	//REDIRECTION

	if (ms_isbuiltin(ms->tmp_pgm->argv))
		ms_select_builtin(ms, ms->tmp_pgm);
	else
	{
		signal(SIGINT, ms_signal_fork);
		signal(SIGQUIT, ms_signal_fork);
		execve(ms->tmp_pgm->homedir, ms->tmp_pgm->argv, NULL);
	}
}
