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

static void		draw_floor(t_ray_cast *rc, t_data *win, int x)
{
	t_dot	flr_w;
	t_dot	flr_c;
	t_dot_i	flr_t;
	double	dst_w;
	double	dst_p;
	double	dst_c;
	double	coeff;
	int		y;

	if (!rc->side && rc->ray_dir.x > 0 && (flr_w.x = rc->map.x))
		flr_w.y = rc->map.y + rc->wall_x;
	else if (!rc->side && rc->ray_dir.x < 0 && (flr_w.x = rc->map.x + 1))
		flr_w.y = rc->map.y + rc->wall_x;
	else if (rc->side && rc->ray_dir.y > 0 && (flr_w.x = rc->map.x + rc->wall_x))
		flr_w.y = rc->map.y;
	else if (rc->side && rc->ray_dir.y < 0 && (flr_w.x = rc->map.x + rc->wall_x))
		flr_w.y = rc->map.y + 1;
	dst_w = rc->perp_wall_dist;
	dst_p = 0;
	if (rc->draw_end < 0)
		rc->draw_end = win->wh;
	y = rc->draw_end;
	while (++y < win->wh)
	{
		dst_c = win->wh / (2.0 * y - win->wh);
		coeff = (dst_c - dst_p) / (dst_w - dst_p);
        flr_c.x = coeff * flr_w.x + (1.0 - coeff) * win->pl->pos.x;
        flr_c.y = coeff * flr_w.y + (1.0 - coeff) * win->pl->pos.y;
		flr_t.x = (int)(flr_c.x * win->tw) % win->tw;
		flr_t.y = (int)(flr_c.y * win->th) % win->th;
		rc->col = (win->texture[6][win->tw * flr_t.y + flr_t.x] >> 1) & 8355711;
		img_pixel_put(win, x, y, rc->col);
		rc->col = (win->texture[7][win->tw * flr_t.y + flr_t.x]);
		img_pixel_put(win, x, win->wh - y, rc->col);
	}
	// int		y;
	// t_dot	floor_w;
	// t_dot	floor_c;
	// t_dot_i	floor_t;
	// double	dist_w;
	// double	dist_c;
	// double	coeff;

	// if (!rc->side && rc->ray_dir.x > 0)
	// {
	// 	floor_w.x = rc->map.x;
	// 	floor_w.y = rc->map.y + rc->wall_x;
	// }
	// else if (!rc->side && rc->ray_dir.x < 0)
	// {
	// 	floor_w.x = rc->map.x + 1;
	// 	floor_w.y = rc->map.y + rc->wall_x;
	// }
	// else if (rc->side && rc->ray_dir.y > 0)
	// {
	// 	floor_w.x = rc->map.x + rc->wall_x;
	// 	floor_w.y = rc->map.y;
	// }
	// else
	// {
	// 	floor_w.x = rc->map.x + rc->wall_x;
	// 	floor_w.y = rc->map.y + 1;
	// }
	// dist_w = rc->perp_wall_dist;
	// if (rc->draw_end < 0)
	// 	rc->draw_end = win->wh;
	// y = rc->draw_end;
	// while (++y < win->wh)
	// {
	// 	dist_c = win->wh / (2 * y - win->wh);
	// 	coeff = dist_c / dist_w;
	// 	floor_c.x = coeff * floor_w.x + (1 - coeff) * win->pl->pos.x;
	// 	floor_c.y = coeff * floor_w.y + (1 - coeff) * win->pl->pos.y;
	// 	floor_t.x = (int)(floor_c.x * win->tw) % win->tw;
	// 	floor_t.y = (int)(floor_c.y * win->th) % win->th;
	// 	rc->col = (win->texture[6][win->tw * floor_t.y + floor_t.x] >> 1) & 8355711;
	// 	img_pixel_put(win, x, y, rc->col);
	// 	rc->col = (win->texture[7][win->tw * floor_t.y + floor_t.x]);
	// 	img_pixel_put(win, x, win->wh - y, rc->col);
	// }
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
	}
	draw_floor(rc, win, x);
}
