#include "minishell.h"

void	ms_exit_status(char **args, int ret)
{
	ret = ft_atoi(args[1]);
	if (ret > 255)
	{
		write(1, "exit\n", 6);
		exit(ret % 256);
	}
	else if (ret < 0)
	{
		write(1, "exit\n", 6);
		exit (ret + 256);
	}
	else
	{
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
	while (pgm->argv[1][i] != '\0')
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
		printf("exit\nminishell: exit: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	ms_exit_status(pgm->argv, 0);
	return (0);
}
