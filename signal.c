/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:09:36 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/27 00:04:31 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ms_signal_act_ctrlc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void ms_signal_desact_ctrlc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void ms_signal_activate(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ms_signal_act_ctrlc);
}

void ms_signal_desactivate(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ms_signal_desact_ctrlc);
}
