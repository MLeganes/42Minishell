/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/03 20:40:03 by amorcill         ###   ########.fr       */
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
	
	get_env(&info, env);
	info.env_ptr_copy = env;	
	while (1)
	{
		signal_init();
		init_struct(&info);
		
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
			write(1, "exit\n", 5);
			//system("leaks minishell");
			exit (0);
		}
		else if (ft_strlen(info.cmdline) > 0)
		{
			add_history(info.cmdline);
			lexer(&info);
			parser(&info);
			execute(&info);
			free_after_cmd(&info);
			//system("leaks minishell");
		}
		//system("leaks minishell");
		// Free a lots of things.
	}	
	return (0);
}
