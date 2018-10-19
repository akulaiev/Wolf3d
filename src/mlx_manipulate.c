/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manipulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:26:05 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/10 14:26:07 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int			exit_x(void)
{
	// system("leaks wolf3d");
	exit(0);
}

int			key_react(int keycode, void *param)
{
	t_data		*p;
	t_player	*play;

	p = (t_data*)param;
	play = p->pl;
	if (keycode == 53)
		exit(0);
	if (keycode == 126) //up arrow
	{
		if (!p->world_map[(int)(play->pos.x + play->dir.x)][(int)play->pos.y] &&
		play->pos.x + play->dir.x > 1)
			play->pos.x += play->dir.x * 0.3;
		if (!p->world_map[(int)play->pos.x][(int)(play->pos.y + play->dir.y)] &&
		play->pos.y + play->dir.y > 1)
			play->pos.y += play->dir.y * 0.3;
	}
	if (keycode == 125) //down arrow
	{
		if (!p->world_map[(int)(play->pos.x - play->dir.x)][(int)play->pos.y] &&
		play->pos.x + play->dir.x < p->mw)
			play->pos.x -= play->dir.x * 0.3;
		if (!p->world_map[(int)play->pos.x][(int)(play->pos.y - play->dir.y)] &&
		play->pos.y + play->dir.y < p->mh)
			play->pos.y -= play->dir.y * 0.3;
	}
	if (keycode == 124) //right arrow
	{
		double old_dir_x = play->dir.x;
		play->dir.x = play->dir.x * cos(-0.3) - play->dir.y * sin(-0.3);
		play->dir.y = old_dir_x * sin(-0.3) + play->dir.y * cos(-0.3);
		double old_plane_x = play->cam_plane.x;
		play->cam_plane.x = play->cam_plane.x * cos(-0.3) - play->cam_plane.y * sin(-0.3);
		play->cam_plane.y = old_plane_x * sin(-0.3) + play->cam_plane.y * cos(-0.3);
	}
	if (keycode == 123) //left arrow
	{
		double old_dir_x = play->dir.x;
		play->dir.x = play->dir.x * cos(0.3) - play->dir.y * sin(0.3);
		play->dir.y = old_dir_x * sin(0.3) + play->dir.y * cos(0.3);
		double old_plane_x = play->cam_plane.x;
		play->cam_plane.x = play->cam_plane.x * cos(0.3) - play->cam_plane.y * sin(0.3);
		play->cam_plane.y = old_plane_x * sin(0.3) + play->cam_plane.y * cos(0.3);
	}
	// mlx_clear_window(p->mlx_p, p->mlx_nw);
	mlx_destroy_image (p->mlx_p, p->mlx_img);
	raycast(p);
	return (0);
}

void		open_win(t_data *win)
{
	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->ww, win->wh, "Test");
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	mlx_hook(win->mlx_nw, 17, 1L << 17, exit_x, (void*)win);
}

void		img_pixel_put(t_data *win, int x, int y, int col)
{
	if (x < win->ww && y < win->wh && x >= 0 && y >= 0)
		*(int*)(win->img_ptr + (x * (win->bits_per_pixel >> 3) +
		y * win->size_line)) = col;
}
