/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/07 11:22:13 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute(t_command *cmd, char **env)
{
	pid_t child_pid;;

	child_pid = fork();
	if (child_pid == 0)
		execve("/bin/ls", cmd->argv, env);
	else
		waitpid(child_pid, 0 , 0);
}

int parse( char *cmdline, t_command *cmd)
{
	char *line;
	int i;
		
	i = 0;
	cmd->argc = 0;
	while (cmdline[i] != '\0' && cmdline[i] != ' ')
	{
		i++;
	}
	line = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(line, cmdline, i + 1);
	printf("len %d, line: %s\n", i, line);
	cmd->argv[cmd->argc] = line;
	cmd->argv[cmd->argc + 1] = NULL;
	printf("coommand; %s\n", cmd->argv[0]);
	
	return (0);
}

void eval(t_command *cmd, char *cmdline)
{
	int background;
	

	printf("Evaluating %s \n", cmdline);
	
	background = parse(cmdline, cmd);
	printf("Found command %s\n", cmd->argv[0]);
		
}

int main(int argc, char **argv, char **env)
{
	t_command cmd;
	char *cmdline;
	char *prompt;
	(void)argv;
	(void)argc;

	prompt = "minishell >";
	while (1)
	{
		printf("minishell >");
		
		cmdline = readline(NULL);
		printf("\n Readed command: %s len: %lu", cmdline, strlen(cmdline));
		break;	
	}
	
	eval(&cmd, cmdline);
	printf("Env %s\n", env[0]);
	execute(&cmd, env);
	return (0);
}