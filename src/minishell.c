/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/05 14:20:29 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal g_sig;

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
	
	/* CTRL + \ ignored */	
	signal(SIGQUIT, SIG_IGN);
	
	get_env(&info, env);
	info.env_ptr_copy = env;	
	while (1)
	{
		//signal_init();
		init_struct(&info);
		
		/***
		 *  Warnning: comment the free(ms->cmdline);
		 ***/
		
		/* testing */
		//info.cmdline = "";
		//info.cmdline = "<< end cat > file";
		//info.cmdline = "echo \"hello ee\" > file";
		//info.cmdline = "ls -la | wc";
		
		//signal(SIGINT, signal_ctrlc);
		//signal(SIGINT, signal_ctrlc);
		

		/*   last chance to do the fucking signals  */
		/* WORKING -- DONOT TOUCH */
		signal(SIGINT, signalhandler_ctrlc);
		
		
		info.cmdline = readline(info.prompt);
		if (info.cmdline == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			//system("leaks minishell");
			exit (0);
		}
		
		/* WORKING -- DONOT TOUCH */
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
