/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:09:36 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/17 21:25:08 by arohmann         ###   ########.fr       */
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

	tcgetattr(0, &mio);
	mio.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &mio);
	signal(SIGINT, SIG_IGN);
}

void	signalhandler_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signalhandler_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
}
