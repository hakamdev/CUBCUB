#ifndef	CUBENGINE_H
# define	CUBENGINE_H

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

// Test
#include <stdio.h>

#define RAD(a) ((float)(a * M_PI / 180))
#define DEG(a) ((float)(a * 180) / M_PI)
#define TILE_SIZE 64
#define FOV 60
#define CUBTITLE "Cub3D by HAKAM"
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0
#define MAX_READ_CONFIG 8
#define IS_ERROR(f) ((f) == ERROR)
#define IS_SUCESS(f) ((f) == SUCCESS)

#define NORTH 0
#define SOUTH 1
#define WEST  2
#define EAST  3
#define SPR	  4
#define HUD   5
#define	CIEL  0
#define FLOOR 1

#define EXT_CUB 0
#define EXT_XPM 1

typedef char	*t_str;
typedef	int		t_bool;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

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

typedef struct	s_map
{
	t_str	row;
	int		columns;
}				t_map;

/* PUT ALL GAME DATA HERE TO AVOID USING THE STUPID G_ PREFIX */
typedef struct s_cub
{
	t_map		*map;
	int			rows;
	t_img		cnvs;
	t_img		txt[6];
	t_color		color[2];
	t_str		fname;
	t_str		errno;
	int			read_nb;
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
int		ft_output(t_str msg, int retcode);
void	ft_free(char **s);
int		get_next_line(int fd, char **line);

int		exit_error( t_cub *cub, t_str error_msg);
int		ft_init_read(t_cub *cub);
int		check_filename(t_str filename, int ext);

#endif