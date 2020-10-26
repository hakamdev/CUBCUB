#ifndef	CUBENGINE_H
# define CUBENGINE_H

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

// Test
# include <stdio.h>
# include <string.h>
//

# define POW(a)			 ((a) * (a))
# define RAD(a)			 ((float)((a) * M_PI / 180))
# define DEG(a)			 ((float)((a) * 180) / M_PI)
# define IS_ERROR(f)	 ((f) == ERROR)
# define IS_SUCESS(f)	 ((f) == SUCCESS)
# define TILE_SIZE		 64
# define FOV			 RAD(60.0F)
# define CUBTITLE		 "CUB3D BY HAKAM"
# define TRUE			 1
# define FALSE			 0
# define ERROR			 -1
# define SUCCESS		 0
# define MAX_READ_CONFIG 9
# define WIN_WIDTH		 cub->cnvs.width
# define WIN_HEIGHT		 cub->cnvs.height

# define NORTH	0
# define SOUTH	1
# define WEST	2
# define EAST	3
# define SPR	4
# define CP		5
# define HUD	6
# define SPLSH	7

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4
# define F 5
# define G 6

# define CIEL  	0
# define FLOOR 	1

# define X 		0
# define Y 		1

# define EXT_CUB 0
# define EXT_XPM 1

# define EV_KEY_PRESSED		2
# define EV_KEY_RELEASED	3

//
# define BITSPERPIXEL 24
# define PLANES 1
# define COMPRESSION 0
# define PIXELBYTESIZE (WIN_WIDTH * WIN_HEIGHT * BITSPERPIXEL / 8)
# define FILESIZE (PIXELBYTESIZE + sizeof(bmp))
# define XPIXELPERMETER 0X130B
# define YPIXELPERMETER 0X130B
# define PIXEL 0XFF
//

typedef char	*t_str;
typedef	int		t_bool;
typedef struct	s_header
{
	char 	type[2];
	uint32_t filesize;
	uint32_t reserved;
	uint32_t offset;
} __attribute__((packed)) t_header;
typedef struct	s_bmpinfo
{
	uint32_t headersize;
	uint32_t width;
	uint32_t height;
	uint16_t  planes;
	uint16_t  bpp;
	uint32_t compression;
	uint32_t imgsize;
	uint32_t xpixelpmeter;
	uint32_t ypixelpmeter;
	uint32_t numclrpalette;
	uint32_t mostimpclr;
} __attribute__((packed)) t_bmpinfo;
typedef struct	s_bmp
{
	t_header	header;
	t_bmpinfo	info;
}				t_bmp;
typedef struct	s_sprite
{
	float	x;
	float	y;
	float	offx;
	float	offy;
	int		p[2];
	float	off[2];
	float	dist;
	float	ang;
	float	scale;
}				t_sprite;
typedef struct	s_color
{
	int r;
	int g;
	int b;
} t_color;
typedef struct	s_camera
{
	float		x;
	float		y;
	int			p[2];
	float		ang;
	float		side_ang;
	float		mov_spd;
	float		rot_spd;
	int			mov_dir;
	int			rot_dir;
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
typedef struct	s_checkpnt
{
	char		name;
	float		x;
	float		y;
}				t_checkpnt;
typedef struct	s_level
{
	t_checkpnt  start;
	t_checkpnt	end;
}				t_level;
typedef struct	s_lvldata
{
	char		current_cp;
	char		last_cp;
	int			cp_nb;
	int			lvl_nb;
	t_level		level[10];
	t_checkpnt	checkps[20];
}				t_lvldata;

typedef struct	s_cub
{
	void		*window;
	void		*mlx;
	int			rows_nb;
	int			sprs_nb;
	int			read_nb;
	int			cp_nb;
	int			level_nb;
	int			currlvl;
	int			currcp;
	char		lastcpn;
	t_str		fname;
	t_str		errno;
	t_map		*map;
	t_sprite	*spr;
	t_ray		*ray;
	t_camera	cam;
	t_img		cnvs;
	t_img		txt[8];
	t_color		color[2];
	t_bool		screenshot;
	t_level		level[10];
	t_checkpnt	checkps[20];
}				t_cub;

t_bool			g_end_splsh;
int				g_indx_splsh;

int		init_camera(t_cub *cub);
t_bool	is_camera(t_cub *cub, int i, int j);
int		set_camera_rotation(t_cub *cub, char direction);
//
int		check_filename(t_str filename, int ext);
int		check_color(t_color color);
int		check_map_element(t_cub *cub, int i, int j);
int		check_map(t_cub *cub);
int		check_args( t_cub *cub, int argc, const t_str *args);
//
int		event_key_pressed(int key, t_cub *cub);
int		event_key_released(int key, t_cub *cub);
int		event_game_loop(t_cub *cub);
//
int		init_read(t_cub *cub);
int		init_mlx(t_cub *cub);
int		init_cam(t_cub *cub);
int		init_cub(t_cub *cub);
int		init_game(t_cub *cub, int ac, t_str *av);
int		init_textures(t_cub *cub);
int		init_textures_extra(t_cub *cub);
int		init_sprites(t_cub *cub);
int		init_rays(t_cub *cub);
//
void	init_ray(t_ray *ray);
void	hori_collision(t_cub *cub, t_rdata *h, t_ray *r);
void	vert_collision(t_cub *cub, t_rdata *v, t_ray *r);
void	update_ray(t_cub *cub, t_ray *ray);
//
int		read_resolution(t_cub *cub, t_str line);
int		read_xpm(t_cub *cub, t_str line, int txt_index);
int		read_color(t_cub *cub, t_str line, int clr_index);
int		read_map(t_cub *cub, t_str line);
int		handle_line(t_cub *cub, t_str line);
//
//void	render_sprite(t_cub *cub, int id, int offx, int offy);
void    render_wall_stripe(t_cub *cub, t_wdata *stripe, int x);
void	render_ciel_stripe(t_cub *cub, int ystart, int yend, int x);
void	render_flor_stripe(t_cub *cub, int ystart, int yend, int x);
//
void	update_camera(t_cub *cub);
void	update_rays(t_cub *cub);
void	update_rendering_walls(t_cub *cub);
void	update_rendering_sprites(t_cub *cub);
void    update_rendering_hud(t_cub *cub, t_img *hud);
//
float	normalize_spr(t_cub *cub, float angle);
void	sort_sprites(t_cub *cub);
int		add_sprite(t_cub *cub, int i, int j);
//
int		clean(t_cub *cub, int retcode);
int		take_screenshot(t_cub *cub);
//
int		get_color_from_txt(t_cub *cub, t_wdata *stripe, int pos[2], int img);
int		color_rgb_to_hex(t_color clr);
float	get_distance(t_cub *cub, float x, float y);
float	normalize_rad(float angle);
char	value_at(t_cub *cub, int x, int y);
void	draw(t_img *canvas, int x, int y, int color);
int		exit_error(t_cub *cub, t_str error_msg);
int		ft_strlen_2d(t_str *str);
int		free_2d(t_str *str);
t_bool	is_wall(t_cub *cub, float x, float y);
t_bool	is_sprite(t_cub *cub, float x, float y);
//
int		ft_atoi(const char *str);
void	ft_free(char **s);
int		get_next_line(int fd, char **line);
int		ft_output(t_str msg, int retcode);
void	ft_putnbr(int n);
char	**ft_split(const char *ss, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
t_bool	ft_strnchar(const char *str, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strsub(char **s, unsigned int start, size_t n);
int		init_splash_screen(t_cub *cub);

int		init_checkpoints(t_cub *cub);
int		init_levels(t_cub *cub);
int		update_level(t_cub *cub);

void	render_sprite(t_cub *cub, int id, int off[2], int spr);
char	value_at_pos(t_cub *cub, int x, int y);

#endif