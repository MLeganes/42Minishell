/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/07 17:20:45 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void open_url(void)
{
	char launch[255];

	sprintf(launch, "open '%s' &", "https://www.42heilbronn.de/en/");
	system(launch);
}

void execute(t_command *cmd, char **env)
{
	pid_t child_pid;
	int		result;

	child_pid = fork();
	printf("PID parent: %d PID child: %d\n", getpid(), (int)child_pid);
	
	if (child_pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
		
	if (child_pid == 0)
	{
		result = execve("/bin/ls", cmd->argv, env);
		if (result < 0)
		{
			perror("Command failed");
			exit(1);
		}
	}
	waitpid(child_pid, 0 , 0);
	printf("else --- PID parent: %d PID child: %d\n", getpid(), (int)child_pid);
	
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

	open_url();

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