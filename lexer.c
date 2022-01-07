#include "minishell.h"

t_token	*new_tok(void *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == 0)
		return (0);
	new->flag = 0;
	new->token = content;
	new->next = NULL;
	return (new);
}

void mini_spliter(t_info *info)
{
	int i;
	int len;
	int start;
	char *str;

	info->cmdline = ft_strtrim(info->cmdline, " \t");
	len = ft_strlen(info->cmdline);
	i = 0;
	start = 0;
	while (i < len)
	{
		if (info->cmdline[i] == ' ')
		{
			str = ft_substr(info->cmdline, start, i);
			// if first time create list
			// else just add it at the end

			info->list = new_tok(str);
			free(str);
			i++;
		}
		// if there is any quote we have to ignore spaces until the next quote
		i++;
	}
}
void lexer(t_info *info)
{
	mini_spliter(info);
	// like split but puts everything in a linked list 
	//and returns a pointer to the first element
}