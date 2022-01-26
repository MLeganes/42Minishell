/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/26 22:11:30 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void exec_program(t_info *ms, int islast)
{
	int fdp[2];
	
	if (ms_isbuiltin(ms->tmp_pgm->argv) && !ms->npipes)
	{
		// Redirection
		// if (ms.redirection......)	/* testing code  */
	// pid_t cpid, w;
    // int wstatus;
	/* end testing code  */		
		ms_select_builtin(ms, ms->tmp_pgm);
	}
	else
	{
		if (pipe(fdp) == -1)
			printf("Pipe Error \n");			
		//printf("Pipe with fd(0): %d and fd[1]: %d\n", fd[0], fd[1]); 
		// if (!strncmp(ms->tmp_pgm->argv[0], "exit", 4) && ms->npipes > 0)
		// {
		// 	exec_parent(ms, fd, islast);
		// 	return ;
		// }
		ms->tmp_pgm->pid = fork();
		if (ms->tmp_pgm->pid < 0)
			printf("Error in fork pid");			
		else if (ms->tmp_pgm->pid == 0)
			exec_child(ms, fdp, islast);
		else
			exec_parent(ms, fdp, islast);	
		ms->idx++;	// Used to indicate there are more than 1 command to close the fd.
	}
}

void init_fd(t_info *ms)
{
	dup2(ms->fd_bak[READ], STDIN_FILENO);
	dup2(ms->fd_bak[WRITE], STDOUT_FILENO);
	// dup2(ms->fd[READ], STDIN_FILENO);
	// dup2(ms->fd[WRITE], STDOUT_FILENO);
}

static void	error_no(t_info *ms)
{
	int		ex;
	int		status;

	while (ms->idx > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			ex = WEXITSTATUS(status);
			(void)ex;
		}
		ms->idx--;
	}
}

void	execute(t_info *ms)
{
	//5rd try!!
	int			islast;

	ms->idx = 0;
	ms->tmp_pgm = ms->pgmlist;
	ms->fd_old[READ] = STDIN_FILENO;
	ms->fd_old[WRITE] = -1;
	while (ms->tmp_pgm)
	{
		islast = 0;
		if (!ms->tmp_pgm->next)
			islast = 1;
		if (ms->tmp_pgm->argv)
		{
			init_fd(ms);
			if (ms->tmp_pgm->argv[0])
				exec_program(ms, islast);
		}
		ms->tmp_pgm = ms->tmp_pgm->next;
	}
	error_no(ms);
}
