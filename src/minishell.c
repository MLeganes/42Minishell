/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/18 05:51:36 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static void	init_struct(t_info *info)
{
	info->prompt = "\001\033[0;32m\002❯\e[1m_\e[0m \001\033[0m\002";
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

static void	minishell(t_info *ms)
{
	if (lexer(ms) == 0)
	{
		errno = 0;
		if (parser(ms) != ERROR)
			execute(ms);
	}
}

int	main(void)
{
	t_info	info;

	//signal(SIGQUIT, SIG_IGN);
	get_env(&info);
	while (1)
	{
		init_struct(&info);
		//sig_setter();
		signals_minishell();
		if (isatty(STDIN_FILENO))
			info.cmdline = readline(info.prompt);
		else
			info.cmdline = minishell_get_next_line(0);
		if (info.cmdline == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDERR_FILENO, "exit\n", 5);
			free_end(&info);
			exit (g_exit_status);
		}
		//sig_unsetter();
		minishell(&info);
		free_after_cmd(&info);
	}
	free_end(&info);
	return (0);
}
