#include "../include/cubengine.h"

t_bool	ft_strnchar(const char *str, char c)
{
	int		i = -1;
	while (str[++i])
		if (str[i] == c)
			return (TRUE);
	return (FALSE);
}