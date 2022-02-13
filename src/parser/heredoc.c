/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:20:06 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/13 21:43:32 by amorcill         ###   ########.fr       */
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

static char	*ms_get_tmp_file(void)
{
	char		*file;
	struct stat	buf;
	int			i;

	i = 1;
	while (i < INT_MAX)
	{
		file = ft_strjoin(".tmp", ft_itoa(i));
		if (stat(file, &buf) == -1)
		{
			return (file);
		}
		if (file)
			free(file);
		i++;
	}
	return (NULL);
}

	/* If delimiter has quote, removed to print it!!! line 56*/
static void	ms_heredoc_writeline(t_info *ms, t_heredoc *hd)
{
	int		i;
	int		j;
	char	*new;

	if (hd->del_qu == 1 || hd->del_qu == 2)
		write(hd->fd, hd->line, ft_strlen(hd->line));
	if (hd->del_qu == 0)
	{
		i = 0;
		while (hd->line[i])
		{
			if (hd->line[i] == '$')
			{
				j = ms_expand_get_len(hd->line, i + 1);
				new = ms_expand_get_value(ms, hd->line, i, j);
				write(hd->fd, new, ft_strlen(new));
				i += j;
			}
			else
				write(hd->fd, &hd->line[i], 1);
			i++;
		}
	}
	write(hd->fd, "\n", 1);
	if (hd->line)
		free(hd->line);
}

int	ms_redir_heredoc(t_info *ms, t_program **pgm)
{
	t_heredoc	hd;

	hd.del_qu = 0;
	hd.fd_stdin = dup(STDIN_FILENO);
	if ( ms->tmp_tkn->next->data == NULL)
	{
		printf("Error: no tmp file for heredoc.\n");
		return (ERROR);
	}
	hd.delim = ms->tmp_tkn->next->data;
	hd.del_qu = ms->tmp_tkn->next->in_dq + ms->tmp_tkn->next->in_q;
	hd.file = ms_get_tmp_file();
	hd.fd = open(hd.file, O_RDWR | O_CREAT, 0644);
	if (hd.fd == -1)
		printf("Error: no tmp file for heredoc.\n");
	hd.exit = 1;
		signal(SIGINT, signalhandler_heredoc);
	while (hd.exit)
	{
		hd.line = readline("> ");
		if (hd.line == NULL)
		{
			write(STDERR_FILENO, "\n", 1);
			hd.exit = 0;
		}
		else if (!ft_strncmp(hd.line, hd.delim, ft_strlen(hd.delim) + 1))
			hd.exit = 0;
		else
			ms_heredoc_writeline(ms, &hd);
	}
	if (write(0, "", 0) == -1)
	{
		dup2(hd.fd_stdin, STDIN_FILENO);
		close(hd.fd_stdin);
		return (ERROR);
	}
	close(hd.fd_stdin);
	close(hd.fd);
	ms_redir_lstadd_last(&(*pgm), new_redirection_heredoc(hd.file, 0, 0));
	return (0);
}
