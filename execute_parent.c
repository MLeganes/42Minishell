/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/24 12:37:01 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_parent(t_info *ms, int fd[2], int old_fd[2],int islast)
{
	int status;
	int res;
	/* testing code  */
	// pid_t cpid, w;
    // int wstatus;
	/* end testing code  */
	
	status =0;
	res = 0;
	
	signal(SIGINT, ms_signal_fork);
	signal(SIGQUIT, ms_signal_fork);
	if (ms->idx > 0)
		close(old_fd[READ]);
	old_fd[READ] = fd[READ];
	old_fd[WRITE] = fd[WRITE];
	close(fd[WRITE]);
	if (islast) //last command. 
		close(fd[READ]);
	
	/* control  
	 waitid(): returns 0 on success or if WNOHANG was specified and no child(ren) 
	 specified by id has yet changed state; on  error,  -1  is  returned.
	*/	
	waitpid(ms->tmp_pgm->pid, &status, 0);
	res  = (WEXITSTATUS(status));
	if ( res == -1)
		printf("minishel: Error [execute_parent.c] \n");

	/* testing code  */
    /* Code executed by parent. #man waitpid */
	// do {
	// 	w = waitpid(ms->tmp_pgm->pid, &status, WUNTRACED | WCONTINUED);
	// 	if (w == -1) {
	// 		perror("waitpid");
	// 		exit(EXIT_FAILURE);
	// 	}

	// 	if (WIFEXITED(wstatus)) {
	// 		printf("exited, status=%d\n", WEXITSTATUS(wstatus));
	// 	} else if (WIFSIGNALED(wstatus)) {
	// 		printf("killed by signal %d\n", WTERMSIG(wstatus));
	// 	} else if (WIFSTOPPED(wstatus)) {
	// 		printf("stopped by signal %d\n", WSTOPSIG(wstatus));
	// 	} else if (WIFCONTINUED(wstatus)) {
	// 		printf("continued\n");
	// 	}
	// } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	// exit(EXIT_SUCCESS);

	/* end testing code  */

	
	return ;
}