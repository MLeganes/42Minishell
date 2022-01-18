/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/17 21:13:01 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void ms_cmd_case_echo(t_token *tk)
{
	tk->cmdname = CMD_ECHO;
	printf("Command is echo cmdname: %d\n", tk->cmdname);
}

static void ms_cmd_case_cd(t_token *tk)
{
	tk->cmdname = CMD_CD;
	printf("Command is cd cmdname: %d\n", tk->cmdname);
}

static void ms_cmd_case_pwd(t_token *tk)
{
	
}

static void ms_cmd_selector(t_info *ms, t_token *tk)
{
	if (ft_strncmp(tk->data, "echo", ft_strlen(tk->data)) == 0)
		ms_cmd_case_echo(tk);
	else if (ft_strncmp(tk->data, "cd", ft_strlen(tk->data)) == 0)
		ms_cmd_case_cd(tk);
	else if (ft_strncmp(tk->data, "pwd", ft_strlen(tk->data)) == 0)
	 	ms_cmd_case_pwd(ms);
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

	tk = ms->list;
	
	/***
	 * Function to do, remove "" from commma d!!
	 * 
	 ***/
	//ms_remove_dquote(tk);
	
	// Only one command.
	if (ms->npipes == 0)
	{
		ms_cmd_selector(ms, tk);
		if (tk->cmdname == CMD_NO_FOUND)
			//stop! display promt??
		
		// execute cmd
		
	}
	// 1 pipes -> 2 commands
	else 
	{
		//Another way is to call exe-func just with the command found.
		/**
		 * while (ms->npipes > 0)
		 * {
		 * 		//call parser
		 * 		// get 
		 * }
		*/
		
	}
	
	/***
	 * 
	 * 
	 ***/
	ms_cmd_path(ms);
	
	// Here, it should be everything in t_info 
	// ready to execute.
}
