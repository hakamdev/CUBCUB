#include "../include/cubengine.h"

int		ft_output(t_str msg, int retcode)
{
	int		len;

	len = ft_strlen(msg);
	write(2, msg, len);
	write(2, "\n\n", 2);
	return (retcode);
}