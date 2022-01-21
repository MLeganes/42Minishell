/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/21 18:28:45 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_struct(t_info *info)
{
	info->prompt = "minishell >";
	info->list = NULL;
	info->cmdline = NULL;
	info->tmp_tkn = NULL;
	info->state = STATE_GENERAL;
	info->idx = 0;
	info->ntok = 0;
	info->npipes = 0;
	info->pgmlist = NULL;
	info->npgms = 0;
}

int main(int argc, char **argv, char **env)
{
	t_info info;

	(void)argv;
	(void)argc;
	(void)env;
	//char *path;
	
	//get_env(&info, env);
	// geting the f* path!!!!
	//get_env_pgmpath(&info, "ls");
	//get_env_path(&info);
	
	
	while (1)
	{
		init_struct(&info);
		/***
		 *  Warnning: comment the free(ms->cmdline);
		 ***/
		//info.cmdline = "ls -la";
		info.cmdline = readline(info.prompt);
		
		add_history(info.cmdline);
		lexer(&info);
		parser(&info);
		execute(&info);
		free_after_cmd(&info);
		//system("leaks minishell");
	}
	
	// free_end(&info);	
	// printf("Env %s\n", env[0]);
	
	return (0);
}