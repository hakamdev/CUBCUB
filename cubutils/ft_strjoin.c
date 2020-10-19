#include "../include/cubengine.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ss;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 && s2)
	{
		ss = ft_strdup(s2);
		return (ss);
	}
	i = -1;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ss = malloc(len1 + len2 + 1)))
		return (NULL);
	while (++i < len1)
		*(ss + i) = *((char *)(s1 + i));
	while (j < len2)
		*(ss + i++) = *((char *)(s2 + j++));
	*(ss + i) = '\0';
	ft_free(&s1);
	return (ss);
}