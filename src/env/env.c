#include "minishell.h"

bool	is_var_delim(char c)
{
	if (c == '=')
		return(true);
	return (false);
}

bool	is_end(char c)
{
	if (c == '\0')
		return (true);
	return (false);
}

t_env	*ms_new_env(char *var, char *content, t_env *next)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->content = content;
	new->next = next;
	return (new);
}

void get_env(t_info *ms, char **env)
{
	int i;
	int	j;

	ms->env_ptr_copy = env;	/* Keep an array copy */
	i = 0;
	ms->env_v = NULL;
	ms->tmp_env = ms->env_v;
	while (env[i])
	{
		j = 0;
		while (is_var_delim(env[i][j]) == false && is_end(env[i][j]) == false)
			j++;
		ms->tmp_env = ms_new_env(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1), ms->tmp_env);
		i++;
	}
	ms->env_v = ms->tmp_env;
	//print_env(ms);
}
