/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 18:00:41 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/17 18:00:44 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void		draw_floor(t_ray_cast *rc, t_data *win, int x, int y)
{
	t_dot	floor;
	t_dot	floor_c;
	t_dot_i	floor_t;
	double	dist_w;
	double	dist_p;
	double	dist_c;
	double	coeff;

	if (!rc->side && rc->ray_dir.x > 0 && (floor.x = rc->map.x))
		floor.y = rc->map.y + rc->wall_x;
	else if (!rc->side && rc->ray_dir.x < 0 && (floor.x = rc->map.x + 1))
		floor.y = rc->map.y + rc->wall_x;
	else if (rc->side && rc->ray_dir.y > 0 && (floor.x = rc->map.x + rc->wall_x))
		floor.y = rc->map.y;
	else if (rc->side && rc->ray_dir.y < 0 && (floor.x = rc->map.x + rc->wall_x))
		floor.y = rc->map.y + 1;
	dist_w = rc->perp_wall_dist;
	dist_p = 0;
	if (rc->draw_end < 0)
		rc->draw_end = win->wh;
	while (++y < win->wh)
	{
		dist_c = win->wh / (2 * y - win->wh);
		coeff = (dist_c - dist_p) / (dist_w - dist_p);
		floor_c.x = coeff * floor.x + (1 - coeff) * win->pl->pos.x;
		floor_c.x = coeff * floor.x + (1 - coeff) * win->pl->pos.y;
		floor_t.x = (int)(floor_c.x * win->tw) % win->tw;
		floor_t.y = (int)(floor_c.y * win->th) % win->th;
		rc->col = (win->texture[6][win->tw * floor_t.y + floor_t.x] >> 1) & 8355711;
		img_pixel_put(win, x, y, rc->col);
		rc->col = (win->texture[7][win->tw * floor_t.y + floor_t.x] >> 1) & 8355711;
		img_pixel_put(win, x, win->wh - y, rc->col);
	}
}

void		draw_y_stripe(t_ray_cast *rc, t_data *win, int x, int y)
{
	while (++y < rc->draw_end)
	{
		rc->delta = y * 256 - win->wh * 128 + rc->line_h * 128;
		rc->tex.y = ((rc->delta * win->th) / rc->line_h) / 256;
		rc->col = win->texture[rc->tex_num][win->th * rc->tex.y + rc->tex.x];
		if (rc->side == 1)
			rc->col = (rc->col >> 1) & 8355711;
		img_pixel_put(win, x, y, rc->col);
		draw_floor(rc, win, x, y);
	}
}
