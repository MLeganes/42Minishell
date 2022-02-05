/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/05 15:05:46 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_struct(t_info *info)
{
	//info->prompt = "minishell >";
	info->prompt = "\001\033[0;32m\002 ❯\e[1m_\e[0m \001\033[0m\002";
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
	
	/* Signal QUIT Ctrl+\ ignored */
	signal(SIGQUIT, SIG_IGN);
	get_env(&info, env);
	info.env_ptr_copy = env;	
	while (1)
	{
		init_struct(&info);
		
		/* Signal INT Ctrl+C new-handler before readline */
		signal(SIGINT, signalhandler_ctrlc);
		
		/* testing minishell with debugger */
		/***
		 *  Warnning: comment the free(ms->cmdline);
		 ***/
		//info.cmdline = "";
		//info.cmdline = "<< end cat > file";
		//info.cmdline = "echo \"hello ee\" > file";
		//info.cmdline = "ls -la | wc";		
		info.cmdline = readline(info.prompt);
		if (info.cmdline == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			//system("leaks minishell");
			exit (0);
		}

		/* Signal INT Ctrl+C ignored after readline to execute everything */
		signal(SIGINT, SIG_IGN);
		
		lexer(&info);
		parser(&info);
		execute(&info);
		free_after_cmd(&info);
		//system("leaks minishell");
		//system("leaks minishell");
		// Free a lots of things.
	}	
	return (0);
}
