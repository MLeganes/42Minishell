/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:09:36 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/04 19:57:28 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// static void signal_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		close(STDIN_FILENO);
// 		write(STDERR_FILENO, "\n", 1);
// 	}
// }

// void	signal_ctrlc_heredoc(void)
// {
// 	signal(SIGINT, signal_heredoc);
// }

// void	signal_dfl(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	//signal(SIGQUIT, SIG_DFL);
// }

void signal_init(void)
{
	g_sig.sig_int = 0;
	g_sig.sig_quit = 0;
	g_sig.exit_status = 0;
	g_sig.pid = 1;
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, signal_ctrlc);
}

/* ctrl + c */
// void signal_int(int sig)
// {
// 	if (SIGINT == sig)
// 	{
// 		if (g_sig.pid == 0)
// 		{
// 			write(1, "\n", 1);
// 			//	write(STDERR_FILENO, "\n", 1);
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 			rl_redisplay();
// 			g_sig.exit_status = 1;
// 		}
// 		else
// 		{
// 			//write(STDERR_FILENO, "\n", 1);
// 			g_sig.exit_status = 130;
// 		}
// 		g_sig.sig_int = 1;
// 	}
// }

/* CTRL + \ used in the child only */
void signal_child_quit(int sig)
{
	if (SIGQUIT == sig)
	{
		write(STDERR_FILENO, "quit: 3", 7);
		g_sig.exit_status = 131;
		g_sig.sig_quit = 1;
	}
}

/* CTRL + C used in the child only */
void signal_child_int(int sig)
{
	if (SIGINT == sig)
	{
		write(STDERR_FILENO, "\n", 1);
		g_sig.exit_status = 130;
		g_sig.sig_int = 1;
	}	
}

// int	prompt_echoctl(bool echoctl)
// {
// 	struct termios	terminos;
// 	int				status;

// 	status = tcgetattr(STDOUT_FILENO, &terminos);
// 	if (status == -1)
// 		return (ERROR);
// 	if (echoctl)
// 		terminos.c_lflag |= ECHOCTL;
// 	else
// 		terminos.c_lflag &= ~(ECHOCTL);
// 	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos);
// 	if (status == -1)
// 		return (ERROR);
// 	return (0);
// }