/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/26 22:29:22 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ms_program_findpath(t_info *ms)
{
	int res;

	res = 0;
	res = get_env_path(ms);
	if (res == 1)
	{
		free(ms->tmp_pgm->argv[0]);
		ms->tmp_pgm->argv[0] = ms->tmp_pgm->homedir;
		ms->tmp_pgm->homedir = NULL;
	}
	else
	{
		// no file found. error
		printf("minishel: No such file or directory [execute.c] ms_program_findpath\n");
	}
}


void exec_child(t_info *ms, int fd[2], int islast)
{	
	(void)islast;
	
	// // child no READ
	// close(fd[READ]);
	// // child want to  WRITE
	// dup2(fd[WRITE], STDOUT_FILENO);
	// close(fd[WRITE]);

	// ms_program_findpath(ms);
	// /***
	//  * execve: result has exited with code 0 (0x00000000) --> OK!!!
	//  ***/
	// execve(ms->tmp_pgm->argv[0], ms->tmp_pgm->argv, ms->env_ptr_copy); 
	// anything after is for error.

	
	if (ms->tmp_pgm->next)
	{ // if pipe, redirection
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
	if (ms_isbuiltin(ms->tmp_pgm->argv) == 1)
		ms_select_builtin(ms, ms->tmp_pgm);
	else
	{
		signal(SIGINT, ms_signal_fork);
		signal(SIGQUIT, ms_signal_fork);
		
		ms_program_findpath(ms);
		/***
		 * execve: result has exited with code 0 (0x00000000) --> OK!!!
		 ***/
		execve(ms->tmp_pgm->argv[0], ms->tmp_pgm->argv, ms->env_ptr_copy);
	}
}
