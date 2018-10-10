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
}				t_data;

typedef struct	s_breth
{
	int		dx;
	int		dy;
	int		dx2;
	int		dy2;
	int		leng_x;
	int		leng_y;
	int		length;
	int		x_inc;
	int		y_inc;
	int		x;
	int		y;
	int		d1;
	int		len_x;
	int		len_y;
}				t_breth;

typedef	struct	s_gradient
{
	int		start_r;
	int		start_g;
	int		start_b;
	int		end_r;
	int		end_g;
	int		end_b;
	int		res_r;
	int		res_g;
	int		res_b;
}				t_gradient;


t_dot			va(t_dot first, t_dot second);
t_dot			vmn(t_dot first, t_dot second);
t_dot			vm(t_dot first, double val);
t_dot			vd(t_dot first, double val);
double			vs(t_dot first, t_dot second);
t_dot			vr(t_dot vec, double angle);
void			normalize(t_dot *ray);
void			img_pixel_put(t_data *win, int x, int y, int col);
void			breth_vertical(int x, int y_start, int y_end, t_col col, t_data *win);
int				exit_x(void);
int				key_react(int keycode, void *param);
void			open_win(t_data *win);
void			img_pixel_put(t_data *win, int x, int y, int col);
void			raycast(t_data *win);

#endif
