/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/26 22:34:22 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_parent(t_info *ms, int fd[2], int islast)
{
	//int status;
	//int res;
	//status =0;
	//res = 0;	
	
	signal(SIGINT, ms_signal_fork);
	signal(SIGQUIT, ms_signal_fork);
	

	if (ms->idx > 0)
		close(ms->fd_old[READ]);
	ms->fd_old[READ] = fd[READ];
	ms->fd_old[WRITE] = fd[WRITE];
	close(fd[WRITE]);
	if (islast) //last command. 
		close(fd[READ]);
	
	// if (!islast)
	// {
	// 	// Parent NO WRITE
	// 	close(fd[WRITE]);
	// 	// Parent want to READ.
	// 	dup2(fd[READ], STDIN_FILENO);
	// 	close(fd[READ]);
	// }
	// else
	// {
	// 	// Parent want to READ.
	// 	dup2(fd[READ], STDIN_FILENO);
	// 	close(fd[READ]);
	// 	// Parent want to WRITE.
	// 	dup2(fd[WRITE], STDOUT_FILENO);
	// 	close(fd[WRITE]);
	// }
	
		// //Parent want to READ.
		// dup2(fd[READ], STDIN_FILENO);
		// close(fd[READ]);
		// // Parent want to WRITE.
		// dup2(fd[WRITE], STDOUT_FILENO);
		// close(fd[WRITE]);

	
	/* control  
	 waitid(): returns 0 on success or if WNOHANG was specified and no child(ren) 
	 specified by id has yet changed state; on  error,  -1  is  returned.
	*/	
	//waitpid(ms->tmp_pgm->pid, &status, 0);
	//waitpid(ms->tmp_pgm->pid, NULL, 0);
	//ms->idx--; //crazy! i know it.
	// res  = (WEXITSTATUS(status));
	// if ( res == -1)
	// 	printf("minishel: Error [execute_parent.c] \n");
	// return ;
}
