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
# define MW 31
# define MH 31

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <string.h>
# include <pthread.h>
# include <sys/types.h>
# include <unistd.h>

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
}				t_data;

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

t_dot			va(t_dot first, t_dot second);
t_dot			vmn(t_dot first, t_dot second);
t_dot			vm(t_dot first, double val);
t_dot			vd(t_dot first, double val);
double			vs(t_dot first, t_dot second);
t_dot			vr(t_dot vec, double angle);
void			normalize(t_dot *ray);
void			img_pixel_put(t_data *win, int x, int y, int col);

#endif
