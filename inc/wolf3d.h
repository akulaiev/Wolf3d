/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:15:31 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/08 11:15:35 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define MW 24
# define MH 24
# define TW 64
# define TH 64

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <string.h>
# include <pthread.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_color;

typedef union	u_col
{
	unsigned int	integer;
	t_color			struct_col;
}				t_col;

typedef struct	s_dot
{
	double			x;
	double			y;
}				t_dot;

typedef struct	s_dot_i
{
	int			x;
	int			y;
}				t_dot_i;

typedef struct	s_player
{
	t_dot			pos;
	t_dot			dir;
	t_dot			cam_plane;
}				t_player;

typedef struct	s_data
{
	void			*mlx_p;
	void			*mlx_nw;
	void			*mlx_img;
	char			*img_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				ww;
	int				wh;
	double			mv_sp;
	double			rot_sp;
	t_player		*pl;
	int				**world_map;
	t_col			**texture;
}				t_data;

typedef struct	s_ray_cast
{
	double			x_norm;
	t_dot			ray_dir;
	t_dot_i			map;
	t_dot			side_dist;
	t_dot			delta_dist;
	double			perp_wall_dist;
	t_dot_i			step;
	int				side;
	int				line_h;
	int				draw_start;
	int				draw_end;
	t_col			col;
	int				tex_num;
	double			wall_x;
	t_dot_i			tex;
	int				delta;
}				t_ray_cast;


t_dot			va(t_dot first, t_dot second);
t_dot			vmn(t_dot first, t_dot second);
t_dot			vm(t_dot first, double val);
t_dot			vd(t_dot first, double val);
double			vs(t_dot first, t_dot second);
void			img_pixel_put(t_data *win, int x, int y, int col);
int				exit_x(void);
int				key_react(int keycode, void *param);
void			open_win(t_data *win);
void			img_pixel_put(t_data *win, int x, int y, int col);
void			raycast(t_data *win);

#endif
