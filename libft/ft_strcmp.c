#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *)s1;
	s2p = (unsigned char *)s2;
	while (*s1p != '\0' && *s2p != '\0' && *s1p == *s2p)
	{
		s1p++;
		s2p++;
	}
	return ((*s1p) - (*s2p));
}
