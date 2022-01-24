/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/24 12:42:47 by amorcill         ###   ########.fr       */
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

static void exec_program(t_info *ms, int old_fd[2], int islast)
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
			///////error_exit(127, "Pipe error\n", 0);
		if (!strncmp(ms->tmp_pgm->argv[0], "exit", 4) && ms->npipes > 0)
		{
			exec_parent(ms, fd, old_fd, islast);
			return ;
		}
		ms->tmp_pgm->pid = fork();
		if (ms->tmp_pgm->pid < 0)
		{
			printf("Error in fork pid");
			/////////error(errno, strerror(errno), 0);
		}
		else if (ms->tmp_pgm->pid == 0)
			exec_child(ms, fd, old_fd);
			//printf("EXECUTE CHILD"); 
		else
			exec_parent(ms, fd, old_fd, islast);
	
		ms->idx++;		
	}
}

void init_fd(t_info *ms)
{
	dup2(ms->fd_new[READ], STDIN_FILENO);
	dup2(ms->fd_new[WRITE], STDOUT_FILENO);
}

void	execute(t_info *ms)
{
	//3rd try!!
	int			islast;
	int			old_fd[2];

	ms->tmp_pgm = ms->pgmlist;
	ms->idx = 0;				// No used for now!
	
	ms->fd_old[READ] = STDIN_FILENO;
	ms->fd_old[WRITE] = -1;
	old_fd[READ] = STDIN_FILENO; //FD_READ 0 = STDIN_FILENO
	old_fd[WRITE] = -1;			//FD WRITE 1 = STDOUT_FILENO
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
				exec_program(ms, old_fd, islast);
		}
		ms->tmp_pgm = ms->tmp_pgm->next;
	}
}




	// program *pgm;
		
	// if (ms->pgmlist != NULL)
	// {
	// 	pgm = ms->pgmlist;
	// 	while (pgm != NULL)
	// 	{
	// 		if (pgm->name == CMD_ECHO)
	// 			return ;
	// 		else if (pgm->name == CMD_CD)
	// 			exe_cd(ms, pgm);
	// 		else if (pgm->name == CMD_PWD)
	// 			return ;
	// 		else if (pgm->name == CMD_EXPORT)
	// 			return ;
	// 		else if (pgm->name == CMD_UNSET)
	// 			return ;
	// 		else if (pgm->name == CMD_ENV)
	// 			return ;
	// 		else if (pgm->name == CMD_EXIT)
	// 			return ;
	// 		//and so on.....
	// 		pgm = pgm->next;
	// 	}
	
	
