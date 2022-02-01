#include "minishell.h"

void	exec_cd(t_info *ms, t_program *pgm)
{
	(void)ms;
	int	res;

	res = 0;
	if (pgm->argv[1])
		res = chdir(pgm->argv[1]);
	if (res == -1)
		printf("minishel: No such file or directory\n");
}
