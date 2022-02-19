/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:22:34 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/19 00:06:06 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*new_redirection(t_info *ms, int is_app, int is_out)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->type = ms->tmp_tkn->type;
	if (ms->tmp_tkn->next && ms->tmp_tkn->next->data)
		new->file = ms->tmp_tkn->next->data;
	else
		error_exit("Redir", "Incomplete command, no file");
	new->is_app = is_app;
	new->is_out = is_out;
	new->next = NULL;
	return (new);
}

int	parser_build_redirection(t_info *ms, t_program **pgm)
{
	t_redir	*redir;
	char	*tmp;

	if (ms->tmp_tkn->type != REDIR_DLESS)
	{
		tmp = ms->tmp_tkn->next->data;
		ms->tmp_tkn->next->data = ft_strtrim(tmp, "'\"");
		free(tmp);
	}
	if (ms->tmp_tkn->type == REDIR_GREAT)
	{
		redir = new_redirection(ms, 0, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DGREAT)
	{
		redir = new_redirection(ms, 1, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_LESS)
	{
		redir = new_redirection(ms, 0, 0);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DLESS)
	{	
		if (ms_redir_heredoc(ms, &(*pgm)) == ERROR)
			return (ERROR);
	}
	ms->tmp_tkn = ms->tmp_tkn->next;
	return (0);
}

static int	ms_redir_in(t_redir *tmp, int inb)
{
	int	fd;

	fd = open(tmp->file, O_RDONLY);
	if (fd < 0)
	{
		if (inb == 1)
			error_exit_errno(1, "Redir", "No such file or directory\n", inb);	
		error_exit_errno(1, "Redir", "No such file or directory", inb);	
		return (0);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
}

static int	ms_redir_out(t_redir *tmp)
{
	int	fd;

	if (tmp->is_app == 1)
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redir_selector(t_info *ms, int inb)
{
	t_redir	*tmp;
	int		status;

	tmp = ms->pgmlist->redir;
	status = 1;
	while (tmp)
	{
		if (tmp->is_out == 0 && tmp->is_app == 0)
			status = ms_redir_in(tmp, inb);
		else if (tmp->is_out == 1)
			ms_redir_out(tmp);
		else
			error_exit_errno(127, "Redir", "Redirection is nonsense", 0);		
		tmp = tmp->next;
	}
	return (status);
}
