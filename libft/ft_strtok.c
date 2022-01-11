#include "libft.h"

char *ft_strtok(char *s, char *delims)
{
	char		*token;
	static char	*ptr;
	int			i;
	int			j;

	token = NULL;
	if (s != NULL)
		ptr = s;
	if (ptr == NULL)
		return (token);
	i = 0;
	while (ptr[i] != '\0')
	{
		j = 0;
		while (delims[j] != '\0')
		{
			if (ptr[i] == delims[j])
				break ;
			j++;
		}
		if (ptr[i] == delims[j])
			break ;
		i++;
	}
	if (ptr[0] != '\0')
	{
		token = ft_substr(ptr, 0, i);
		ptr = ptr + i;
	}
	else
		ptr = NULL;
	return (token);
}

int	main(int argc, char **argv)
{
	char	*ptr;
	(void)argc;
	(void)argv;

	ptr = ft_strtok("how are you ?", " \n\t\0");
	while (ptr != NULL) 
	{
		printf("token : |%s|\n", ptr);
		ptr = ft_strtok(NULL, " \n\t");
	}
	return (0);
}