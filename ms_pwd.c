
#include "minishell.h" 

static void exec_pwd(t_info *ms, t_program *pgm)
{
	(void)ms;
	(void)pgm;
}

void ms_pwd(t_info *ms, t_program *pgm)
{
	exec_pwd(ms, pgm);
}