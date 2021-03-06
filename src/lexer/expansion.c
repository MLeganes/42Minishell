/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:39:46 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/18 20:00:15 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_loop_var(t_info *ms, char *str, int *err)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			k = ms_exp_var(ms, &tmp, str, &i);
			if (k == -1)
				return (ms_error_return(tmp, str, err, 1));
			i += k;
		}
		else
		{
			tmp = ms_append_char(tmp, str[i]);
			i++;
		}
	}
	if (tmp != NULL)
		ms_end_tmp(&tmp, &i);
	free_str(str);
	return (tmp);
}

int	expansion(t_info *ms)
{
	int	err;

	err = 1;
	ms->tmp_tkn = ms->list;
	while (ms->tmp_tkn != NULL)
	{
		if (ft_strchr(ms->tmp_tkn->data, '$') != 0
			&& ft_strchr(ms->tmp_tkn->data, '\'') == 0
			&& ft_strchr(ms->tmp_tkn->data, '"') == 0)
			ms->tmp_tkn->data = ms_loop_var(ms, ms->tmp_tkn->data, &err);
		if (err == -1)
		{
			return (-1);
		}
		ms->tmp_tkn = ms->tmp_tkn->next;
	}
	return (0);
}
