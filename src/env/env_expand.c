/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:33:43 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/05 22:20:25 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	Used by heredoc. */
int	ms_expand_get_len(char *s, int i)
{
	int	count;

	count = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '?')
			return (count);
		count++;
		i++;
	}
	return (count);
}

/* 	Used by heredoc. */
char	*ms_expand_get_value(t_info *ms, char *s, int i, int ret)
{
	char	*line;
	char	*tmp;

	(void)ms;
	tmp = ft_substr(s, i + 1, ret);
	line = getenv(tmp);
	if (!line)
		line = "";
	if (!ft_strncmp(tmp, "_", 2))
	{
		free(tmp);
		tmp = line;
		line = ft_strrchr(line, '/');
		line++;
	}
	else if (s[i + 1] == '?')
		line = ft_itoa(errno);
	free(tmp);
	return (line);
}
