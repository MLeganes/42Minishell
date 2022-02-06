#include "minishell.h"

static char	*ms_append_char(char *str, char c)
{
	char	*tmp;

	if (str == NULL)
	{
		tmp = ft_calloc(sizeof(char), 2);
		tmp[0] = c;
		return (tmp);
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (tmp == NULL)
		return (NULL);
	ft_memcpy(tmp, str, ft_strlen(str) + 1);
	tmp[ft_strlen(str)] = c;
	free(str);
	return (tmp);
}

static int	ms_quotes(char **tmp, char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\'')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	(*i)++;
	while (str[(*i)] != '\0')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	if (str[(*i)] == '\0')
		(*tmp) = ms_append_char((*tmp), '\0');
	return (0);
}

static int	ms_exp_var(t_info *ms, char **tmp, char *str, int *i)
{
	char	*var;
	int		k;

	k = 0;
	var = NULL;
	while (str[(*i) + k] != '\"')
		k++;
	(*tmp) = ms_append_char((*tmp), '\0');
	var = ft_substr(str, (*i) + 1, (k - 1));
	if ((ms->tmp_env = ms_find_env_var(ms, &var)) == NULL)
		return (-1);
	(*tmp) = ft_strjoin((*tmp), ms->tmp_env->content);
	(*tmp) = ms_append_char((*tmp), '\0');
	free(var);
	return (k);
}

static int	ms_d_quotes(t_info *ms, char **tmp, char *str, int *i)
{
	int	k;

	k = 0;
	while (str[(*i)] != '\"' && str[(*i)] != '\0' && str[(*i)] != '$')
	{
		(*tmp) = ms_append_char((*tmp), str[(*i)]);
		(*i)++;
	}
	if (str[(*i)] == '$')
	{
		if ((k = ms_exp_var(ms, tmp, str, i)) == -1)
			return (-1);
		(*i) += k;
	}
	else
	{
		if (str[(*i)] == '\"')
			(*i)++;
		while (str[(*i)] != '\0' && str[(*i)] != '$')
		{
			(*tmp) = ms_append_char((*tmp), str[(*i)]);
			(*i)++;
		}
		if (str[(*i)] == '\0')
			(*tmp) = ms_append_char((*tmp), '\0');
	}
	return (0);
}



static char	*ms_del_quotes(t_info *ms, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			ms_quotes(&tmp, str, &i);
		else if (str[i] == '\"')
		{
			i++;
			if (ms_d_quotes(ms, &tmp, str, &i) == -1)
				return (NULL);
		}
		else
		{
			tmp = ms_append_char(tmp, str[i]);
			i++;
		}
	}
	i = ft_strlen(tmp);
	tmp[i] = '\0';
	if (str != NULL)
		free(str);
	return (tmp);
}

int	ms_handle_quotes(t_info *ms)
{
	ms->tmp_tkn = ms->list;
	while (ms->tmp_tkn != NULL)
	{
		ms->tmp_tkn->data = ms_del_quotes(ms, ms->tmp_tkn->data);
		if (ms->tmp_tkn->data == NULL)
		{
			free_list(ms);
			printf("error: no such variable\n");
			return (-1);
		}
		ms->tmp_tkn = ms->tmp_tkn->next;
	}
	return (0);
		//system ("leaks minishell");
}

void	quotes(t_info *info)
{
	// function to delete quotes and expand vars if $ AND "" if '' it's a literall string
	ms_handle_quotes(info);
	//print_quotes(info);
	// function to put the files after redirections in linked list 
	// function to put args and cmd together
}
