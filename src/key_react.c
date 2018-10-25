/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_react.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:16:29 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/25 17:16:30 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void		move(t_data *p, t_player *play, int keycode)
{
	if (keycode == 126)
	{
		if (!p->map[(int)(play->pos.x + play->dir.x)][(int)play->pos.y] &&
		play->pos.x + play->dir.x * 0.3 > 1 &&
		play->pos.x + play->dir.x * 0.3 < p->mw)
			play->pos.x += play->dir.x * 0.3;
		if (!p->map[(int)play->pos.x][(int)(play->pos.y + play->dir.y)] &&
		play->pos.y + play->dir.y * 0.3 > 1 &&
		play->pos.y + play->dir.y * 0.3 < p->mh)
			play->pos.y += play->dir.y * 0.3;
	}
	if (keycode == 125)
	{
		if (!p->map[(int)(play->pos.x - play->dir.x)][(int)play->pos.y] &&
		play->pos.x - play->dir.x * 0.3 < p->mw &&
		play->pos.x - play->dir.x * 0.3 > 1)
			play->pos.x -= play->dir.x * 0.3;
		if (!p->map[(int)play->pos.x][(int)(play->pos.y - play->dir.y)] &&
		play->pos.y - play->dir.y * 0.3 < p->mh &&
		play->pos.y - play->dir.y * 0.3 > 1)
			play->pos.y -= play->dir.y * 0.3;
	}
	mlx_destroy_image(p->mlx_p, p->mlx_img);
	raycast(p);
}

static void		turn_around(t_data *p, t_player *play, int keycode)
{
	double dr_x;
	double pln_x;

	if (keycode == 124)
	{
		dr_x = play->dir.x;
		play->dir.x = play->dir.x * cos(-0.3) - play->dir.y * sin(-0.3);
		play->dir.y = dr_x * sin(-0.3) + play->dir.y * cos(-0.3);
		pln_x = play->cam_plane.x;
		play->cam_plane.x = play->cam_plane.x * cos(-0.3) -
		play->cam_plane.y * sin(-0.3);
		play->cam_plane.y = pln_x * sin(-0.3) + play->cam_plane.y * cos(-0.3);
	}
	if (keycode == 123)
	{
		dr_x = play->dir.x;
		play->dir.x = play->dir.x * cos(0.3) - play->dir.y * sin(0.3);
		play->dir.y = dr_x * sin(0.3) + play->dir.y * cos(0.3);
		pln_x = play->cam_plane.x;
		play->cam_plane.x = play->cam_plane.x * cos(0.3) -
		play->cam_plane.y * sin(0.3);
		play->cam_plane.y = pln_x * sin(0.3) + play->cam_plane.y * cos(0.3);
	}
	mlx_destroy_image(p->mlx_p, p->mlx_img);
	raycast(p);
}

int				key_react(int keycode, void *param)
{
	t_data		*p;
	t_player	*play;

	p = (t_data*)param;
	play = p->pl;
	if (keycode == 53)
		exit(0);
	if (keycode == 126 || keycode == 125)
		move(p, play, keycode);
	if (keycode == 124 || keycode == 123)
		turn_around(p, play, keycode);
	if (keycode == 12)
	{
		if (p->tex_set == 0)
			p->tex_set = 1;
		else if (p->tex_set == 1)
			p->tex_set = 0;
		mlx_destroy_image(p->mlx_p, p->mlx_img);
		tex_gen(p);
		raycast(p);
	}
	return (0);
}
