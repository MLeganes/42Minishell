/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/01 22:11:17 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_child(t_info *ms, int fd[2])
{	
	int		redirstatus;

	if (ms->tmp_pgm->next)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
	}
	if (ms->fd_old[WRITE] != -1)
	{
		close(ms->fd_old[WRITE]);
		dup2(ms->fd_old[READ], STDIN_FILENO);
		close(ms->fd_old[READ]);
	}	
	//REDIRECTION
	redirstatus = ms_redir_selector(ms, 1);
	if (ms_isbuiltin(ms->tmp_pgm->argv) == 1 && redirstatus)
		ms_select_builtin(ms, ms->tmp_pgm);
	else
	{
		/***
		 * execve: result has exited with code 0 (0x00000000) --> OK!!!
		 ***/
		execve(ms->tmp_pgm->argv[0], ms->tmp_pgm->argv, ms->env_ptr_copy);
	}
}
