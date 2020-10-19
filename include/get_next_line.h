/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:26:09 by ehakam            #+#    #+#             */
/*   Updated: 2020/10/19 20:08:01 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


#  define NL '\n'
#  define CNULL '\0'
#  define INULL 0
#  define ERR -1
#  define BUFFER_SIZE 1024
#  define MAXINT 2147483647
#  define MAXFD 4864
#  define BS_VALID(BS)  (((BS) < (MAXINT) && (BS) >= (0)) ? 1 : 0)
#  define FD_VALID(FD)  (((FD) >= 0 && (FD) <= (MAXFD)) ? 1 : 0)
#  define EXIT_CODE(V)  (V) > 0 ? 1 : (V)
#  define EXIT(EXT_CD)  return (EXT_CD)

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strsub(char **s, unsigned int start, size_t n);
void	ft_free(char **s);

#endif
