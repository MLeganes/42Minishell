/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/05 14:48:31 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_program(t_info *ms, int islast)
{
	int fdp[2];
	
	if (isbuiltin(ms->tmp_pgm->argv) && !ms->npipes)
	{
		if (redir_selector(ms, 0))
			builtin_selector(ms, ms->tmp_pgm);	
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
		
		/* To check or DELETE, everything below*/
		//ms_signal_desactivate();
		
		
		ms->tmp_pgm->pid = fork();
		g_sig.pid = ms->tmp_pgm->pid;
		
		if (ms->tmp_pgm->pid < 0)
			printf("Error in fork pid");			
		else if (ms->tmp_pgm->pid == 0)
		{
			/* WORKING -- DONOT TOUCH */
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exec_child(ms, fdp);
		}
		else
			exec_parent(ms, fdp, islast);
		
		/* To check or DELETE, everything below*/
		//ms_signal_activate();
		
		ms->idx++;// Used to indicate there are more than 1 command to close the fd.
	}
}

static void update_fd(t_info *ms)
{
	if (ms->idx > 0)
	{
		dup2(ms->fd_bak[READ], STDIN_FILENO);
		dup2(ms->fd_bak[WRITE], STDOUT_FILENO);
	}
}

void	execute(t_info *ms)
{
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
			update_fd(ms);
			if (isbuiltin(ms->tmp_pgm->argv) == 0)
				ms_program_updatepath(ms);
			if (ms->tmp_pgm->argv[0])
				exec_program(ms, islast);
		}
		ms->tmp_pgm = ms->tmp_pgm->next;
	}
}
