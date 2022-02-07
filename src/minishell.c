/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/07 15:17:11 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_var;

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

int	main(int argc, char **argv, char **env)
{
	t_info	info;

	(void)argv;
	(void)argc;
	signal(SIGQUIT, SIG_IGN);
	get_env(&info, env);
	info.env_ptr_copy = env;
	while (1)
	{
		init_struct(&info);
		/* Signal INT Ctrl+C apply handler */
		signal(SIGINT, signalhandler_ctrlc);
		
		/* testing minishell with debugger */
		/***
		 *  Warnning: comment the free(ms->cmdline);
		 ***/
		//info.cmdline = "";
		//info.cmdline = "<< end cat > file";
		//info.cmdline = "echo \"hello ee\" > file";
		//info.cmdline = "ls -la | wc";		
		//info.cmdline = "<<";		
		info.cmdline = readline(info.prompt);
		if (info.cmdline == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit (0);
		}

		/* Signal INT Ctrl+C ignored after readline to execute everything */
		signal(SIGINT, SIG_IGN);			
		//system("leaks minishell");
		//system("leaks minishell");
		// Free a lots of things.
		if (lexer(&info) == 0)
		{
			parser(&info);
			execute(&info);
			free_after_cmd(&info);
			printf("%i\n", g_exit_status);
		}
		system("leaks minishell");
	}	
	return (0);
}
		//system("leaks minishell");
		// Free a lots of things.
