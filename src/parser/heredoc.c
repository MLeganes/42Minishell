/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:20:06 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/19 19:44:26 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*new_redirection_heredoc(char *file, int is_app, int is_out)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->type = REDIR_DLESS;
	new->file = file;
	new->is_app = is_app;
	new->is_out = is_out;
	new->next = NULL;
	return (new);
}

static void	ms_heredoc_writeline(t_info *ms, t_heredoc *hd)
{
	int		ij[2];
	char	*new;

	if (hd->del_qu == 1 || hd->del_qu == 2)
		write(hd->fd, hd->line, ft_strlen(hd->line));
	if (hd->del_qu == 0)
	{
		ij[0] = 0;
		while (hd->line[ij[0]])
		{
			if (hd->line[ij[0]] == '$')
			{
				ij[1] = ms_expand_get_len(hd->line, ij[0] + 1);
				new = ms_expand_get_value(ms, hd->line, ij[0], ij[1]);
				write(hd->fd, new, ft_strlen(new));
				ij[0] += ij[1];
			}
			else
				write(hd->fd, &hd->line[ij[0]], 1);
			ij[0]++;
		}
	}
	write(hd->fd, "\n", 1);
	if (hd->line)
		free(hd->line);
}

static int	ms_redir_heredoc_signal(t_heredoc *hd)
{
	dup2(hd->fd_stdin, STDIN_FILENO);
	close(hd->fd_stdin);
	return (ERROR);
}

static void	ms_redir_heredoc_close(t_heredoc *hd)
{
	close(hd->fd_stdin);
	close(hd->fd);
}

int	ms_redir_heredoc(t_info *ms, t_program **pgm)
{
	t_heredoc	hd;

	ms_redir_heredoc_init(&hd, ms);
	sig_setter_hd();
	while (hd.exit && hd.ret)
	{
		hd.line = readline("> ");
		if (hd.line == NULL)
		{
			write(STDERR_FILENO, "\n", 1);
			hd.exit = 0;
		}
		else if (!ft_strncmp(hd.line, hd.delim, ft_strlen(hd.delim) + 1))
		{
			free(hd.line);
			hd.exit = 0;
		}
		else
			ms_heredoc_writeline(ms, &hd);
	}
	if (write(0, "", 0) == -1 || errno == EBADF)
		return (ms_redir_heredoc_signal(&hd));
	ms_redir_heredoc_close(&hd);
	ms_redir_lstadd_last(&(*pgm), new_redirection_heredoc(hd.file, 0, 0));
	return (EXIT_SUCCESS);
}
