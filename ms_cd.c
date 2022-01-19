#include "minishell.h"

static void exe_cd(t_info *ms, t_program *pgm)
{
	(void)ms;
	int		i;
	int 	flag;
	char	*path;
	char	*buff;

	flag = 0;
	i = 0;
	
	// To delete, for testing
	buff = malloc(sizeof(char) * 100);
	path = getcwd(buff, 50);
	printf("CD path before get it %s\n", path);
	while (ft_strncmp(pgm->argv[i], "-n", 2) == 0 && pgm->argv[i] != NULL)
	{
		i++;
		flag = 1;
		/* code */
	}
	
	// update relative and absolute path.
	chdir(pgm->argv[1]);
	if (flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);

	//Maybe is needed to update env PWD?????
	
	// to delete, testing
	path = getcwd(buff, 50);
	printf("CD path after get it %s\n", path);
}

void ms_cd(t_info *ms, t_program *pgm)
{
	exe_cd(ms, pgm);
}