/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/03 20:53:00 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_parent(t_info *ms, int fd[2], int islast)
{
	int status;

	status =0;
	if (ms->idx > 0)
		close(ms->fd_old[READ]);
	ms->fd_old[READ] = fd[READ];
	ms->fd_old[WRITE] = fd[WRITE];
	close(fd[WRITE]);
	if (islast) 
		close(fd[READ]);

	//signal_dfl();
	/* control  
	 waitid(): returns 0 on success or if WNOHANG was specified and no child(ren) 
	 specified by id has yet changed state; on  error,  -1  is  returned.
	*/	
	waitpid(ms->tmp_pgm->pid, &status, 0);
	
	ms->idx--;
	if (WEXITSTATUS(status) == -1)
		printf("minishel: Error [execute_parent.c] \n");
}
