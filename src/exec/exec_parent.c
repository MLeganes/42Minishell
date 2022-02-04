/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/04 19:49:37 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void parent_waitpid(pid_t pid)
{
	int status;

	status =0;
	waitpid(pid, &status, 0);
	
	/* error handler -- another way */
	// if (g_sig.sig_int == 1 || g_sig.sig_quit == 1)
	// 	status = g_sig.exit_status;
	// else if ((status) == 32256 || (status) == 32512)
	// 	status = ((status) / 256);

	/* Commented, there is a signal for childs */
	// if (WIFSIGNALED(status))
	// {
	// 	if (WTERMSIG(status) == 3)
	// 	{
	// 		write(STDERR_FILENO, "Quit: 3\n", 8);
	// 	}
	// 	else if (WTERMSIG(status) == 2)
	// 		write(STDERR_FILENO, "\n", 1);
	// 	//print_error_signaled(WTERMSIG(status), name);
	// 	status = 128 + WTERMSIG(status);
	// }
	// else if (WIFEXITED(status))
	// 	status = WEXITSTATUS(status);
}

void exec_parent(t_info *ms, int fd[2], int islast)
{
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

	//waitpid(ms->tmp_pgm->pid, &status, 0);
	parent_waitpid(ms->tmp_pgm->pid);
	/* actudate the status in the env */
	

	ms->idx--;
	
}
