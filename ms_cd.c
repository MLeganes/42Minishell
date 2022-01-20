#include "minishell.h"

static void exe_cd(t_info *ms, t_program *pgm)
{
	(void)ms;
	int	res;

	res = 0;
	if (pgm->argv[1])
		res = chdir(pgm->argv[1]);
	if (res == -1)
		printf("minishel: No such file or directory\n");
}

void ms_cd(t_info *ms, t_program *pgm)
{
	exe_cd(ms, pgm);
}