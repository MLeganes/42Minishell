/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/21 16:22:41 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_init_fd(t_info *ms)
{
	(void)ms;
	// dup2(ms->std_in, STDIN_FILENO);
	// dup2(ms->std_out, STDOUT_FILENO);
}

static void ms_program_findpath(t_info *ms)
{
	(void)ms;
	int res;

	res = 0;
		//get_env(&info, env);
	// geting the f* path!!!!
	//get_env_pgmpath(&info, "ls");
	res = get_env_path(ms);
	if (res == 0)
		return ; // free everthing and show promt!!!
}

int	ms_isbuiltin(char **argv)
{
	if (ft_strlen(argv[0]) == 3 && !ft_strncmp(argv[0], "pwd", 3))
		return (1);
	else if (ft_strlen(argv[0]) == 2 && !ft_strncmp(argv[0], "cd", 2))
		return (1);
	else if (ft_strlen(argv[0]) == 4 && !ft_strncmp(argv[0], "echo", 4))
		return (1);
	else if (ft_strlen(argv[0]) == 3 && !ft_strncmp(argv[0], "env", 3))
		return (1);
	else if (ft_strlen(argv[0]) == 6 && !ft_strncmp(argv[0], "export", 6))
		return (1);
	else if (ft_strlen(argv[0]) == 5 && !ft_strncmp(argv[0], "unset", 5))
		return (1);
	else if (ft_strlen(argv[0]) == 4 && !ft_strncmp(argv[0], "exit", 4))
		return (1);
	return (0);
}

static void	exec_select_builtin(t_info *ms, t_program *pgm)
{
	if (ft_strlen(pgm->argv[0]) == 3 && !ft_strncmp(pgm->argv[0], "pwd", 3))
		ms_pwd(ms, pgm);
	else if (ft_strlen(pgm->argv[0]) == 2 && !ft_strncmp(pgm->argv[0], "cd", 2))
		ms_cd(ms, pgm);
	// else if (ft_strlen(pgm->argv[0]) == 4 && !ft_strncmp(pgm->argv[0], "echo", 4))
	// 	ms_echo(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 3 && !ft_strncmp(pgm->argv[0], "env", 3))
	// 	ms_env(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 6 && !ft_strncmp(pgm->argv[0], "export", 6))
	// 	ms_export(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 5 && !ft_strncmp(pgm->argv[0], "unset", 5))
	// 	ms_unset(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 4 && !ft_strncmp(pgm->argv[0], "exit", 4))
	// 	ms_exit(pgm);
	return ;
}

static void exec_program(t_info *ms, int old_fd[2], int islast)
{
	int fd[2];
	
	if (ms_isbuiltin(ms->tmp_pgm->argv) && ms->npipes == 0)
	{
		// Redirection
		// if (ms.redirection......)
		
		exec_select_builtin(ms, ms->tmp_pgm);
	}
	else
	{
		if (pipe(fd) == -1)
			///////error_exit(127, "Pipe error\n", 0);
		if (!strncmp(ms->tmp_pgm->argv[0], "exit", 4) && ms->npipes > 0)
		{
			exec_parent(fd, old_fd, islast);
			return ;
		}
		ms->tmp_pgm->pid = fork();
		if (ms->tmp_pgm->pid < 0)
		{
			printf("Error in fork pid");
			/////////error(errno, strerror(errno), 0);
		}
		else if (ms->tmp_pgm->pid == 0)
			printf("EXECUTE CHILD"); 
			//exec_child(ms, fd, old_fd);
		else
			exec_parent(fd, old_fd, islast);
		ms->idx++;
	}
}

void	execute(t_info *ms)
{
	//2nd try!!
	int			islast;
	int			old_fd[2];
	

	ms->tmp_pgm = ms->pgmlist;
	ms->idx = 0;				// using here as well.
	old_fd[READ] = STDIN_FILENO; //FD_READ 0 = STDIN_FILENO
	old_fd[WRITE] = -1;			//FD WRITE 1 = STDOUT_FILENO
	while (ms->tmp_pgm)
	{
		islast = 0;
		if (ms->tmp_pgm->next == NULL)
			islast = 1;
		if (ms->tmp_pgm->argv)
		{
			//exec_init_fd(ms);
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
	
	
