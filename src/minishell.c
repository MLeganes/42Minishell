/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/20 20:46:35 by arohmann         ###   ########.fr       */
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

static int	checks_syntax(t_token *token, int i)
{
	if ((token->type == PIPE && token->next->type == PIPE)
		|| (token->type == REDIR_GREAT && token->next->type == REDIR_GREAT)
		|| (token->type == REDIR_GREAT && token->next->type == REDIR_LESS)
		|| (token->type == REDIR_LESS && token->next->type == REDIR_LESS)
		|| (token->type == REDIR_LESS && token->next->type == REDIR_GREAT)
		|| (token->type == REDIR_DLESS && token->next->type == REDIR_DLESS)
		|| (token->type == REDIR_DGREAT
			&& token->next->type == REDIR_DGREAT)
		|| (token->type == REDIR_DGREAT
			&& (ft_strcmp(token->next->data, "") == 0))
		|| (token->type == REDIR_DLESS
			&& (ft_strcmp(token->next->data, "") == 0))
		|| (token->type == REDIR_LESS
			&& (ft_strcmp(token->next->data, "") == 0))
		|| (token->type == REDIR_GREAT
			&& (ft_strcmp(token->next->data, "") == 0))
		|| (token->type == PIPE && (ft_strcmp(token->next->data, "") == 0))
		|| (i == 0 && token->type == PIPE))
		return (1);
	return (0);
}

static int	syntax_check(t_info *ms)
{
	int		i;
	t_token	*token;

	token = ms->list;
	i = 0;
	while (token != NULL)
	{
		if (checks_syntax(token, i) == 1)
		{
			error_exit(token->data, "Syntax error near unexpected token");
			g_exit_status = 2;
			return (ERROR);
		}
		token = token->next;
		i++;
	}
	return (0);
}

static void	minishell(t_info *ms)
{
	sig_unsetter();
	if ((lexer(ms) == 0) && (syntax_check(ms) == 0))
	{
		errno = 0;
		if (parser(ms) != ERROR)
			execute(ms);
	}
	free_after_cmd(ms);
	fds_reset(ms);
}

int	main(void)
{
	t_info	info;

	signal(SIGQUIT, SIG_IGN);
	get_env(&info);
	fds_copy(&info);
	while (1)
	{
		init_struct(&info);
		sig_setter();
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
		minishell(&info);
	}
	free_end(&info);
	return (0);
}
