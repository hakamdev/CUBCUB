#ifndef	CUBENGINE_H
# define	CUBENGINE_H

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

// Test
#include <stdio.h>
//

#define POW(a)			((a) * (a))
#define RAD(a)			((float)((a) * M_PI / 180))
#define DEG(a)			((float)((a) * 180) / M_PI)
#define IS_ERROR(f)		((f) == ERROR)
#define IS_SUCESS(f)	((f) == SUCCESS)
#define TILE_SIZE		100
#define FOV				RAD(60.0F)
#define CUBTITLE		"CUB3D BY HAKAM"
#define TRUE			1
#define FALSE			0
#define ERROR			-1
#define SUCCESS			0
#define MAX_READ_CONFIG	8
#define WIN_WIDTH		cub->cnvs.width
#define WIN_HEIGHT		cub->cnvs.height

#define NORTH 0
#define SOUTH 1
#define WEST  2
#define EAST  3
#define SPR	  4
#define HUD   5

#define	CIEL  0
#define FLOOR 1

#define	X 0
#define Y 1

#define EXT_CUB 0
#define EXT_XPM 1

#define EV_KEY_PRESSED	2
#define EV_KEY_RELEASED	3

typedef char	*t_str;
typedef	int		t_bool;
typedef struct	s_sprite
{
	int		x;
	int		y;
	float	offx;
	float	offy;
	int		p[2];
	float	off[2];
	float	dist;
	float	ang;
	int		scale;
}				t_sprite;
typedef struct	s_color
{
	int r;
	int g;
	int b;
} t_color;
typedef struct	s_camera
{
	int			x;
	int			y;
	int			p[2];
	float		ang;
	float		mov_spd;
	float		rot_spd;
	t_bool		mov_dir;
	t_bool		rot_dir;
}				t_camera;
typedef struct	s_rdata
{
	float		hit[2];
	float		inter[2];
	float		step[2];
	float		dist;
}				t_rdata;
typedef struct	s_wdata
{
	float		top;
	float		bttm;
	float		height;
}				t_wdata;
typedef struct	s_ray
{
	float		dist;
	float		ang;
	float		hit[2];
	t_bool		dir[4];
	t_bool		hitver;
}				t_ray;
typedef struct	s_img
{
	t_str path;
	void *img;
	int	*data;
	float hratio;
	float vratio;
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
typedef struct s_cub
{
	void		*window;
	void		*mlx;
	int			rows_nb;
	int			sprs_nb;
	int			read_nb;
	t_str		fname;
	t_str		errno;
	t_map		*map;
	t_sprite	*spr;
	t_ray		*ray;
	t_camera	cam;
	t_img		cnvs;
	t_img		txt[6];
	t_color		color[2];
	t_bool		screenshot;
}				t_cub;

/* FUNCTIONS */
char	**ft_split(const char *ss, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strsub(char **s, unsigned int start, size_t n);
int		ft_atoi(const char *str);
void	ft_putnbr(int n);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_bool	ft_strnchar(const char *str, char c);
int		ft_output(t_str msg, int retcode);
void	ft_free(char **s);
int		get_next_line(int fd, char **line);
int		exit_error( t_cub *cub, t_str error_msg);
int		ft_init_read(t_cub *cub);
int		check_filename(t_str filename, int ext);
char	value_at(t_cub *cub, int x, int y);
void	draw(t_img *canvas, int x, int y, int color);
float	normalize_rad(float angle);
float	get_distance(t_cub *cub, float x, float y);
t_bool	is_wall(t_cub *cub, int i, int j);
void	update_walls_rendering(t_cub *cub);

#endif