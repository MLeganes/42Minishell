/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:09:36 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/18 05:51:45 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_setter(void)
{
	struct termios mio;

	tcgetattr(0, &mio);
	mio.c_lflag = ~ECHOCTL;
	tcsetattr(0, 0, &mio);
	signal(SIGINT, signalhandler_ctrlc);
}

void	sig_unsetter(void)
{
	struct termios mio;

	tcgetattr(1, &mio);
	mio.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &mio);
	signal(SIGINT, SIG_IGN);
}

void	signalhandler_ctrlc(int sig)
{			
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_minishell(void)
{		
	signal(SIGINT, signalhandler_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_fork(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	signalhandler_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
}