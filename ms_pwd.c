
#include "minishell.h" 

static void exec_pwd(t_info *ms, t_program *pgm)
{
	(void)ms;
	(void)pgm;

	char	*cwd;
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
}

void ms_pwd(t_info *ms, t_program *pgm)
{
	exec_pwd(ms, pgm);
}