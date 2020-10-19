#include "../include/cubengine.h"

void	ft_free(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}