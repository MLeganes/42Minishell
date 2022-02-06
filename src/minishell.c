/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/06 14:03:47 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_info *info)
{
	info->prompt = "\001\033[0;32m\002 ❯\e[1m\e[0m \001\033[0m\002";
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
		signal(SIGINT, signalhandler_ctrlc);
		info.cmdline = readline(info.prompt);
		if (info.cmdline == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit (0);
		}
		signal(SIGINT, SIG_IGN);
		lexer(&info);
		parser(&info);
		execute(&info);
		free_after_cmd(&info);
	}	
	return (0);
}
		//system("leaks minishell");
		//system("leaks minishell");
		// Free a lots of things.
