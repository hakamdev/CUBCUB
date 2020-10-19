/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:22:33 by ehakam            #+#    #+#             */
/*   Updated: 2020/10/19 20:07:02 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	ft_find_index(const char *s, char c)
{
	int		i;

	if (s)
	{
		i = 0;
		while ((char)s[i])
		{
			if ((char)s[i] == c)
				EXIT(i);
			i++;
		}
	}
	EXIT(ERR);
}

static int	ft_handle_nl(char **v_line, char **v_temp, char **v_rest)
{
	int		nl_index;
	char	*v_addup;

	nl_index = ft_find_index(*v_temp, NL);
	if (nl_index != ERR)
	{
		if (!(v_addup = ft_strsub(v_temp, 0, nl_index)))
			EXIT(ERR);
		if (!(*v_line = ft_strjoin(*v_line, v_addup)))
			EXIT(ERR);
		if (!(*v_rest = ft_strdup(&v_temp[0][nl_index + 1])))
			EXIT(ERR);
		ft_free(&v_addup);
		ft_free(v_temp);
		EXIT(1);
	}
	EXIT(INULL);
}

static int	ft_handle_rest(char **v_line, char **v_temp, char **v_rest)
{
	int		ret;

	if (*v_rest)
	{
		if (ft_find_index(*v_rest, NL) > ERR)
		{
			ft_free(v_temp);
			*v_temp = *v_rest;
			if ((ret = ft_handle_nl(v_line, v_temp, v_rest)) != INULL)
				EXIT(ret);
		}
		else
		{
			if (!(*v_line = ft_strjoin(*v_line, *v_rest)))
				EXIT(ERR);
			ft_free(v_rest);
		}
	}
	EXIT(INULL);
}

int			get_next_line(int fd, char **line)
{
	static char	*rest[MAXFD];
	char		*temp;
	int			sread;
	int			ret;

	if (!line || !BS_VALID(BUFFER_SIZE) || !FD_VALID(fd) ||
			read(fd, NULL, 0) == ERR || !(temp = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		EXIT(ERR);
	sread = 0;
	if (!(*line = ft_strdup("")))
		EXIT(ERR);
	if ((ret = ft_handle_rest(line, &temp, &rest[fd])) != INULL)
		EXIT(ret);
	while ((sread = read(fd, temp, BUFFER_SIZE)) > INULL)
	{
		temp[sread] = CNULL;
		if (ft_find_index(temp, NL) > ERR)
			if ((ret = ft_handle_nl(line, &temp, &rest[fd])) != INULL)
				EXIT(ret);
		if (!(*line = ft_strjoin(*line, temp)))
			EXIT(ERR);
	}
	if (!sread)
		ft_free(&temp);
	EXIT(EXIT_CODE(sread));
}
