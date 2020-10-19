#ifndef	CUBENGINE_H
# define	CUBENGINE_H

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define RAD(a) ((float)(a * M_PI / 180))
#define DEG(a) ((float)(a * 180) / M_PI)
#define TILE_SIZE 64
#define FOV 60
#define CUBTITLE "Cub3D by HAKAM"
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0
#define IS_ERROR(f) ((f) == ERROR)
#define IS_SUCESS(f) ((f) == SUCCESS)

typedef char	*t_str;
typedef	int		t_bool;

typedef struct	s_img
{
	t_str path;
	void *img;
	int	*data;
	int	width;
	int	height;
	int bpp;
	int sl;
	int end;
}				t_img;

/* PUT ALL GAME DATA HERE TO AVOID USING THE STUPID G_ PREFIX */
typedef struct s_cub
{
	t_img		cnvs;
	t_img		txt[4];
	t_img		sp;
	t_img		hud;
	t_str		fname;
	t_str		errno;
	t_bool		screenshot;
}				t_cub;

/* GLOBALS */

/* FUNCTIONS */
int		ft_atoi(const char *str);
void	ft_putnbr(int n);
char	**ft_split(const char *ss, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strsub(char **s, unsigned int start, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_next_line(int fd, char **line);

#endif