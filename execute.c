/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/25 19:37:36 by amorcill         ###   ########.fr       */
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

static void exec_program(t_info *ms, int islast)
{
	int fd[2];
	
	if (ms_isbuiltin(ms->tmp_pgm->argv) && ms->npipes == 0)
	{
		// Redirection
		// if (ms.redirection......)		
		ms_select_builtin(ms, ms->tmp_pgm);
	}
	else
	{
		if (pipe(fd) == -1)
			printf("Pipe Error \n"); 
			///////error_exit(127, "Pipe error\n", 0);
		printf("Pipe with fd(0): %d and fd[1]: %d", fd[0], fd[1]); 
		if (!strncmp(ms->tmp_pgm->argv[0], "exit", 4) && ms->npipes > 0)
		{
			exec_parent(ms, fd, islast);
			return ;
		}
		ms->tmp_pgm->pid = fork();
		if (ms->tmp_pgm->pid < 0)
		{
			printf("Error in fork pid");			
		}
		else if (ms->tmp_pgm->pid == 0)
			exec_child(ms, fd);
			//printf("EXECUTE CHILD"); 
		else
			exec_parent(ms, fd, islast);
	
		ms->idx++;	// Used to indicate there are more than 1 command to close the fd.
	}
}

void init_fd(t_info *ms)
{
	dup2(ms->fd[READ], STDIN_FILENO);
	dup2(ms->fd[WRITE], STDOUT_FILENO);
}

void	execute(t_info *ms)
{
	//3rd try!!
	int			islast;

	ms->idx = 0;
	ms->tmp_pgm = ms->pgmlist;
	ms->fd_old[READ] = STDIN_FILENO;
	ms->fd_old[WRITE] = -1;
	
	while (ms->tmp_pgm)
	{
		islast = 0;
		if (ms->tmp_pgm->next == NULL)
			islast = 1;
		if (ms->tmp_pgm->argv)
		{
			init_fd(ms);
			if (ms_isbuiltin(ms->tmp_pgm->argv) == 0)
				ms_program_findpath(ms);
			if (ms->tmp_pgm->argv[0])
				exec_program(ms, islast);
		}
		ms->tmp_pgm = ms->tmp_pgm->next;
	}
}
