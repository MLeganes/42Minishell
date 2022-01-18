/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/18 17:50:35 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exe_cd(t_info *ms, t_program *pgm)
{
	char *path;
	char *buff;
	(void)ms;
	(void)pgm;

	// To delete, for testing
	buff = malloc(sizeof(char) * 100);
	path = getcwd(buff, 50);
	printf("CD path before get it %s\n", path);
	
	// update relative and absolute path.
	chdir(pgm->argv[1]);

	//Maybe is needed to update env PWD?????
	
	// to delete, testing
	path = getcwd(buff, 50);
	printf("CD path after get it %s\n", path);
}

void	execute(t_info *ms)
{
	t_program *pgm;
	
	
	if (ms->pgmlist != NULL)
	{
		pgm = ms->pgmlist;
		while (pgm != NULL)
		{
			if (pgm->name == CMD_ECHO)
				return ;
			else if (pgm->name == CMD_CD)
				exe_cd(ms, pgm);
			else if (pgm->name == CMD_PWD)
				return ;
			else if (pgm->name == CMD_EXPORT)
				return ;
			else if (pgm->name == CMD_UNSET)
				return ;
			else if (pgm->name == CMD_ENV)
				return ;
			else if (pgm->name == CMD_EXIT)
				return ;
			//and so on.....
			pgm = pgm->next;
		}
	}
}
