/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/24 13:46:51 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_child(t_info *ms, int fd[2])
{	
	if (ms->tmp_pgm->next)
	{ // if pipe, redirection
		close(fd[READ]);
		dup2(fd[WRITE], STDIN_FILENO);
		close(fd[WRITE]);
	}
	if (ms->fd_old[WRITE] != -1)
	{  // no pipe, std out.
		close(ms->fd_old[WRITE]);
		dup2(ms->fd_old[READ], STDIN_FILENO);
		close(ms->fd_old[READ]);
	}	
	//REDIRECTION
	if (ms_isbuiltin(ms->tmp_pgm->argv) == 1)
		ms_select_builtin(ms, ms->tmp_pgm);
	else
	{
		signal(SIGINT, ms_signal_fork);
		signal(SIGQUIT, ms_signal_fork);
		/***
		 * execve: result has exited with code 0 (0x00000000) --> OK!!!
		 ***/
		execve(ms->tmp_pgm->argv[0], ms->tmp_pgm->argv, ms->env_ptr_copy);
	}
}
