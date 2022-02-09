#include "minishell.h"

void ms_exit_status(char **args, int ret)
{
	ret = ft_atoi(args[1]);
	if (ret > 255)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 6);
		exit(ret % 256);
	}
	else if (ret < 0)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 6);
		exit (ret + 256);
	}
	else
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 6);
		exit(ret);
	}
}

int	exec_exit(t_program *pgm)
{
	int	i;

	i = 0;
	if (pgm->argv[1] == NULL)
		exit(g_exit_status);
	while ((ft_strcmp(pgm->argv[1], "") == 0) || pgm->argv[1][i] != '\0')
	{
		if (ft_isdigit(pgm->argv[1][i]) != 1)
		{
			ft_putstr_fd("exit\n", 2);
			error_exit(pgm->argv[0], "numeric argument required");
			exit(255);
		}
		i++;
	}
	if (pgm->argv[2] != NULL)
	{

		ft_putstr_fd("exit\n", 2);
		error_exit(pgm->argv[0], " too many arguments");
		g_exit_status = 1;
		return (1);
	}
	ms_exit_status(pgm->argv, 0);
	return (0);
}
