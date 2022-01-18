/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/18 17:49:45 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_program *new_program()
{
	t_program *new;
	
	new = (t_program *)malloc(sizeof(t_program));
	if (new == NULL)
		return (NULL);
	new->name = CMD_NONE;
	new->option = NULL;
	new->argv = NULL;
	new->std_in = 0;
	new->std_out = 0;
	new->homedir = NULL;
	new->next = NULL;
	return (new);
}

static t_program *ms_program_lstlast(t_program *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void ms_program_lstadd_last(t_program **lst, t_program *new)
{
	t_program *last;
	
	if (*lst == NULL)
		*lst = new;
	last = ms_program_lstlast(*lst);
	last->next = new;
	new->next = NULL;
}

static void ms_cmd_case_echo(t_info *ms, t_token *tk)
{
	(void)ms;
	tk->cmdname = CMD_ECHO;
	// path = env(cd)
	// path = env(pwd)
	
	printf("Command is echo cmdname: %d\n", tk->cmdname);
}

static void ms_cmd_case_cd(t_info *ms, t_token *tk)
{
	t_program *p;

	tk->cmdname = CMD_CD;
	p = new_program();
	if ( p == NULL)
		return ;
	p->name = CMD_CD;
	p->argv = (char **) malloc(sizeof(char **) * 2); // protection!!
	p->argv[0] = ft_strdup("cd");
	if (tk->next == NULL)
		p->argv[1] = NULL;
	else
	{
		// WARNING::
		// NO MALLOC -- copy ref to pointer DATA!!!!!!!
		p->argv[1] = tk->next->data; //path to change
	}	
	// p->option; //no needed
	// p->path;   //no needed	
	ms_program_lstadd_last(&ms->pgmlist, p);
	
	printf("Command is cd cmdname: %d\n", tk->cmdname);
}

// static void ms_cmd_case_pwd(t_info *ms, t_token *tk)
// {
	
// }

static void ms_cmd_selector(t_info *ms, t_token *tk)
{
	if (ft_strncmp(tk->data, "echo", 4) == 0)
		ms_cmd_case_echo(ms, tk);
	else if (ft_strncmp(tk->data, "cd", 2) == 0)
		ms_cmd_case_cd(ms, tk);
	//else if (ft_strncmp(tk->data, "pwd", ft_strlen(tk->data)) == 0)
	//	ms_cmd_case_pwd(ms, tk);
	// else if (ft_strncmp(tk->data, "export", ft_strlen(tk->data)) == 0)
	// 	ms_cmd_case_export(ms);	
	// else if (ft_strncmp(tk->data, "unset", ft_strlen(tk->data)) == 0)
	// 	ms_cmd_case_unset(ms);
	// else if (ft_strncmp(tk->data, "env", ft_strlen(tk->data)) == 0)
	// 	ms_cmd_case_env(ms);
	// else if (ft_strncmp(tk->data, "exit", ft_strlen(tk->data)) == 0)
	// 	ms_cmd_case_exit(ms);
}

/***
 * Function to do, remove "" from commma d!!
 * 
 ***/
// static void ms_cmd_remove_dquote(t_token **tk)
// {
// 	ft_isdquoute((*tk)->data);
// 	ft_strchr((*tk)->data, '"');
// 	ft_strrchr((*tk)->data, '"');
// }


void	parser(t_info *ms)
{
	
	// check 1° eleme list if cmd exist.
	//ms_parser_cmd(ms);

	t_token *tk;

	/***
	 * Function to do, remove "" from commma d!!
	 * 
	 ***/
	//ms_remove_dquote(ms);
	
	// Only one command.
	if (ms->list != NULL && ms->npipes == 0)
	{
		tk = ms->list;
		ms_cmd_selector(ms, tk); 
		if (ms->pgmlist == NULL)
			return ;	//stop! display promt??
		//
		// ready to execute cmd
	}
	else if (ms->list != NULL && ms->npipes > 0)
	{
		/**tk = ms->list:
		 * while (ms->npipes > 0)
		 * {
		 * 		//call parser ms_cmd_selector
		 * 		//if cmd-found
		 * 		// do next
		 * 		// ms->npipes--;
		 * 		// tk = tk->next:
		 * }
		*/
	}	

	// Here, it should be everything in t_info 
	// ready to execute.
}
