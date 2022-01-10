#include "minishell.h"

t_token	*new_tok(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == 0)
		return (0);
	new->type = 0;
	new->data = content;
	new->next = NULL;
	return (new);
}
t_token	*toklast(t_token *tok)
{
	while (tok != NULL && tok->next != NULL)
	{
		tok = tok->next;
	}
	return (tok);
}

void	tokadd_back(t_token **tok, t_token *new)
{
	t_token	*last;

	if (*tok == NULL)
	{
		*tok = new;
		return ;
	}
	last = toklast(*tok);
	last->next = new;
	new->next = NULL;
}

void	argsplit(char *str, t_info *info)
{
	int i;
	int len;
	int w;
	int start;
	t_token *new;

	i = 0;
	len = 0;
	w = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			len++;
			while (str[i] != '"')
			{	
				i++;
				len++;
			}
		}
		else if (str[i] == ' ' || str[i + 1] == '\0')
		{
			printf("str; %s\n ",ft_substr(str, start, len + 1));
			new = new_tok(ft_substr(str, start, len + 1));
			tokadd_back(&info->list, new);
			start = len;
			len = 0;
			w++;
		}
		i++;
		len++;
	}
}
void mini_spliter(t_info *info)
{
	int i;
	//t_token *new;
	//char **str;

	argsplit(info->cmdline, info);
		printf("hey\n");
/* 	i = 0;
	while (str[i] != 0)
	{
			new = new_tok(str);
			tokadd_back(&info->list, new);
			i++;
	} */
	i = 0;
	while ( i < 2/* info->list->next != NULL */)
	{
		printf("val: %s\n", info->list->data);
		info->list = info->list->next;
		i++;
	}
}
void lexer(t_info *info)
{
	mini_spliter(info);
	// like split but puts everything in a linked list 
	//and returns a pointer to the first element
}