/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/27 00:05:29 by amorcill         ###   ########.fr       */
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
	(void)argv;
	(void)argc;
	t_info info;
	char *path;
	
	get_env(&info, env);
	path = ms_get_path(env, "wc");
	printf("\npath %s\n\n", path);
	ms_signal_activate();
	info.env_ptr_copy = env;
	while (1)
	{
		init_struct(&info);
		/***
		 *  Warnning: comment the free(ms->cmdline);
		 ***/
		//info.cmdline = "ls -la | wc";
		info.cmdline = readline(info.prompt);
		
		add_history(info.cmdline);
		lexer(&info);
		parser(&info);
		execute(&info);
		free_after_cmd(&info);
		//system("leaks minishell");
	}	
	return (0);
}
