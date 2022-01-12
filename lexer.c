#include "minishell.h"

t_token	*new_tok(int len)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == 0)
		return (0);

	new->type = TOKEN;
	new->data = ft_calloc(sizeof(char), len + 1);
	if (new->data == NULL)
		return (NULL);
	new->next = NULL;
	new->len = 0;
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

// void	tokadd_back(t_token **tok, t_token *new)
// {
// 	t_token	*last;

// 	if (*tok == NULL)
// 	{
// 		*tok = new;
// 		return ;
// 	}
// 	last = toklast(*tok);
// 	last->next = new;
// 	new->next = NULL;
// }

// void	argsplit(char *str, t_info *ms)
// {
// 	int i;
// 	int len;
// 	int w;
// 	int start;
// 	t_token *new;

// 	i = 0;
// 	len = 0;
// 	w = 0;
// 	start = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			len++;
// 			while (str[i] != '"')
// 			{	
// 				i++;
// 				len++;
// 			}
// 		}
// 		else if (str[i] == ' ' || str[i + 1] == '\0')
// 		{
// 			printf("str; %s\n ",ft_substr(str, start, len + 1));
// 			new = new_tok(ft_substr(str, start, len + 1));
// 			tokadd_back(&ms->list, new);
// 			start = len;
// 			len = 0;
// 			w++;
// 		}
// 		i++;
// 		len++;
// 	}
// }


static int ms_chartype(char c)
{
	if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == 0)
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

void	ms_case_quote(int chartype, t_info *ms)
{
	if (chartype == CHAR_QUOTE )
		ms->state = STATE_IN_QUOTE;
	else if (chartype == CHAR_DQUOTE )
		ms->state = STATE_IN_DQUOTE;	
	ms->tmp_tkn->type = TOKEN;
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
}

static void ms_case_escapes(t_info *ms)
{
	ms->tmp_tkn->type = TOKEN;
	ms->idx++;
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->cmdline[ms->idx];
	ms->tmp_tkn->len++;
}

static void ms_case_general(t_info *ms)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
	ms->tmp_tkn->type = TOKEN;
}

static void ms_case_whitespace(t_info *ms)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = '\0';
	ms->tmp_tkn->next = new_tok(ft_strlen(ms->cmdline) - ms->idx);
	ms->tmp_tkn = ms->tmp_tkn->next;
	ms->tmp_tkn->type = CHAR_NULL;
}

static void ms_case_multiple(t_info *ms, int chartype)
{
	if (ms->tmp_tkn->len > 0)
		ms_case_whitespace(ms);
		
	// next token
	ms->tmp_tkn->data[0] = chartype;
	ms->tmp_tkn->data[1] = '\0';
	ms->tmp_tkn->type = chartype;

	ms->tmp_tkn->next = new_tok(ft_strlen(ms->cmdline) - ms->idx);
	ms->tmp_tkn = ms->tmp_tkn->next;
	ms->tmp_tkn->type = CHAR_NULL;
}

static void ms_state_selector(t_info *ms, int chartype)
{
	if (chartype == CHAR_QUOTE || chartype == CHAR_DQUOTE)
		ms_case_quote(chartype, ms);
	else if (chartype == CHAR_ESCAPESEQUENCE)
		ms_case_escapes(ms);
	else if (chartype == CHAR_GENERAL)
		ms_case_general(ms);
	else if (chartype == CHAR_WHITESPACE)
	{
		if (ms->tmp_tkn->len > 0)
			ms_case_whitespace(ms);
	}	
	else if (chartype == CHAR_SEMICOLON || chartype == CHAR_GREATER || chartype == CHAR_LESSER 
		|| chartype == CHAR_AMPERSAND || chartype == CHAR_PIPE)
	{		
		// end the token that was being read before
		ms_case_multiple(ms, chartype);		
	}
}

static void ms_state_dquote(t_info *ms, int chartype)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
	if (chartype == CHAR_DQUOTE)
		ms->state = STATE_GENERAL;
}

static void ms_state_quote(t_info *ms, int chartype)
{
	ms->tmp_tkn->data[ms->tmp_tkn->len] = ms->tmp_c;
	ms->tmp_tkn->len++;
	if (chartype == CHAR_QUOTE)
		ms->state = STATE_GENERAL;
}

static void	ms_end_tok(t_info *ms)
{
	if (ms->tmp_tkn->len > 0)
	{
		ms->tmp_tkn->data[ms->tmp_tkn->len] = '\0';
		ms->ntok++;
		ms->tmp_tkn->len = 0;
	}
}

static void	mini_spliter(t_info *ms)
{
	int chartype;

	
	//ft_strtrim(ms->cmdline, " \t");
	
	ms->list = new_tok(ft_strlen(ms->cmdline));
	
	//token = ms->list;
	ms->tmp_tkn = ms->list; 
	while (ms->cmdline[ms->idx] != '\0')
	{
		chartype = ms_chartype(ms->cmdline[ms->idx]);
		ms->tmp_c = ms->cmdline[ms->idx];
		
		if (ms->state == STATE_GENERAL)
			ms_state_selector(ms, chartype);
		else if (ms->state == STATE_IN_DQUOTE)
			ms_state_dquote(ms, chartype);
		else if (ms->state == STATE_IN_QUOTE)
			ms_state_quote(ms, chartype);
		if (chartype == CHAR_NULL)
			ms_end_tok(ms);
		ms->idx++;
	}
}

static void ms_print(t_info *ms)
{
	int i;
	t_token *token;

	token = ms->list;
/* 	printf("Token: %s\n", token->data);
	token = token->next;
	printf("Token: %s\n", token->data);
	token = token->next;
	printf("Token: %s\n", token->data);
	token = token->next;
	printf("Token: %s\n", token->data);
	token = token->next; */
	//token = ms->tmp_tkn;
	//printf("Token: %s\n", token->data);
	// token = ms->tmp_tkn->next;
	// printf("Token: %s\n", token->data);
	i = 0;
	while ( token->next != NULL)
	{
		printf(GREEN"%d: "RE, i);
		printf("%s\t", token->data);
		if (token->next != NULL)
			token = token->next;
		i++;
	}

	printf(GREEN"%d: "RE, i);
	printf("%s\t", token->data);
	printf("\n");
}

void lexer(t_info *ms)
{
	// like split but puts everything in a linked list 
	//and returns a pointer to the first element
	mini_spliter(ms);

	ms_print(ms);
	
}

