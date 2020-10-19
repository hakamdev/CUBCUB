#include "../include/cubengine.h"

char	*ft_strdup(const char *s)
{
	char	*ss;
	size_t	lens;
	size_t	i;

	i = 0;
	lens = ft_strlen(s);
	if (!(ss = (char *)malloc((lens + 1) * sizeof(char))))
		return (NULL);
	while (i < lens)
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}