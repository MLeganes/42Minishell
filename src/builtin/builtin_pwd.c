
#include "minishell.h" 

void	exec_pwd(t_info *ms, t_program *pgm)
{
	(void)ms;
	(void)pgm;

	char	*cwd;
	cwd = getcwd(NULL, 0);
	if ( cwd == NULL)
		printf("minishel: No such file or directory\n");
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
}
