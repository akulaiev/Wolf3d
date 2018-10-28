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

void			move(t_data *p, t_player *play)
{
	if (p->keys->up == 1)
	{
		if (!p->map[(int)(play->pos.x + play->dir.x)][(int)play->pos.y] &&
		play->pos.x + play->dir.x * 0.05 > 1 &&
		play->pos.x + play->dir.x * 0.05 < p->mw)
			play->pos.x += play->dir.x * 0.05;
		if (!p->map[(int)play->pos.x][(int)(play->pos.y + play->dir.y)] &&
		play->pos.y + play->dir.y * 0.05 > 1 &&
		play->pos.y + play->dir.y * 0.05 < p->mh)
			play->pos.y += play->dir.y * 0.05;
	}
	if (p->keys->down == 1)
	{
		if (!p->map[(int)(play->pos.x - play->dir.x)][(int)play->pos.y] &&
		play->pos.x - play->dir.x * 0.05 < p->mw &&
		play->pos.x - play->dir.x * 0.05 > 1)
			play->pos.x -= play->dir.x * 0.05;
		if (!p->map[(int)play->pos.x][(int)(play->pos.y - play->dir.y)] &&
		play->pos.y - play->dir.y * 0.05 < p->mh &&
		play->pos.y - play->dir.y * 0.05 > 1)
			play->pos.y -= play->dir.y * 0.05;
	}
}

void			turn_around(t_data *p, t_player *play)
{
	double dr_x;
	double pln_x;

	if (p->keys->left == 1)
	{
		dr_x = play->dir.x;
		play->dir.x = play->dir.x * cos(-0.05) - play->dir.y * sin(-0.05);
		play->dir.y = dr_x * sin(-0.05) + play->dir.y * cos(-0.05);
		pln_x = play->cam_plane.x;
		play->cam_plane.x = play->cam_plane.x * cos(-0.05) -
		play->cam_plane.y * sin(-0.05);
		play->cam_plane.y = pln_x * sin(-0.05) + play->cam_plane.y * cos(-0.05);
	}
	if (p->keys->right == 1)
	{
		dr_x = play->dir.x;
		play->dir.x = play->dir.x * cos(0.05) - play->dir.y * sin(0.05);
		play->dir.y = dr_x * sin(0.05) + play->dir.y * cos(0.05);
		pln_x = play->cam_plane.x;
		play->cam_plane.x = play->cam_plane.x * cos(0.05) -
		play->cam_plane.y * sin(0.05);
		play->cam_plane.y = pln_x * sin(0.05) + play->cam_plane.y * cos(0.05);
	}
}

static void		key_down_help(int keycode, t_data *p)
{
	if (keycode == 126)
		p->keys->up = 1;
	else if (keycode == 125)
		p->keys->down = 1;
	else if (keycode == 124)
		p->keys->left = 1;
	else if (keycode == 123)
		p->keys->right = 1;
}

int				key_down(int keycode, void *param)
{
	t_data		*p;

	p = (t_data*)param;
	if (keycode == 53)
		exit(0);
	if (keycode == 36)
	{
		if (p->tex_set == 0)
			p->tex_set = 1;
		else if (p->tex_set == 1)
			p->tex_set = 0;
		tex_gen(p);
	}
	if (keycode == 49)
	{
		if (!p->cw)
			p->cw = 1;
		else
			p->cw = 0;
	}
	else
		key_down_help(keycode, p);
	return (0);
}

int				key_up(int keycode, void *param)
{
	t_data		*p;

	p = (t_data*)param;
	if (keycode == 126)
		p->keys->up = 0;
	else if (keycode == 125)
		p->keys->down = 0;
	else if (keycode == 124)
		p->keys->left = 0;
	else if (keycode == 123)
		p->keys->right = 0;
	return (0);
}
