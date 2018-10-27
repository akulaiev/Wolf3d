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

typedef struct	s_key
{
	int				up;
	int				down;
	int				left;
	int				right;
}				t_key;

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
	int				**map;
	int				**texture;
	int				tex_n;
	int				tex_set;
	int				tw;
	int				th;
	int				mw;
	int				mh;
	int				cw;
	t_key			*keys;
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
	int				col;
	int				tex_num;
	double			wall_x;
	t_dot_i			tex;
	int				delta;
}				t_ray_cast;

typedef struct	s_flr
{
	t_dot			flr_w;
	t_dot			flr_c;
	t_dot_i			flr_t;
	double			dst_w;
	double			dst_p;
	double			dst_c;
	double			coeff;
}				t_flr;

typedef struct	s_parce
{
	int				**map;
	int				mw;
	int				mh;
	t_dot			pos;

}				t_parce;

typedef struct	s_read_file
{
	char			*tmp_line;
	int				j;
	int				k;
	int				mw_temp;
}				t_read_file;

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
void			draw_y_stripe(t_ray_cast *rc, t_data *win, int x, int y);
void			parser(t_data *win, int fd);
void			tex_gen(t_data *w);
void			check_case_first(t_read_file rf, t_parce *res);
void			check_other_cases(t_read_file rf, t_parce *res, int check_type);
void			move(t_data *p, t_player *play);
void			turn_around(t_data *p, t_player *play);
int				key_down(int keycode, void *param);
int				key_up(int keycode, void *param);

#endif
