#include "../include/cubengine.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		i;

	i = 0;
	while (i < n-1 && s1[i] 
			&& s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}