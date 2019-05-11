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

static void		draw_floor_help(t_data *win, int x, int y, t_flr f)
{
	int		col;

	while (++y < win->wh)
	{
		f.dst_c = win->wh / (2.0 * y - win->wh);
		f.coeff = (f.dst_c - f.dst_p) / (f.dst_w - f.dst_p);
		f.flr_c.x = f.coeff * f.flr_w.x + (1 - f.coeff) * win->pl->pos.x;
		f.flr_c.y = f.coeff * f.flr_w.y + (1 - f.coeff) * win->pl->pos.y;
		f.flr_t.x = (int)(f.flr_c.x * win->tw) % win->tw;
		f.flr_t.y = (int)(f.flr_c.y * win->th) % win->th;
		col = (win->texture[win->tex_n][win->tw * f.flr_t.y + f.flr_t.x] >> 1)
		& 8355711;
		img_pixel_put(win, x, y, col);
		col = (win->texture[win->tex_n + 1][win->tw * f.flr_t.y + f.flr_t.x]);
		img_pixel_put(win, x, win->wh - y, col);
	}
}

static void		draw_floor(t_ray_cast *rc, t_data *win, int x)
{
	t_flr	f;
	int		y;

	if (!rc->side && rc->ray_dir.x > 0 &&
	(f.flr_w.x = rc->map.x))
		f.flr_w.y = rc->map.y + rc->wall_x;
	else if (!rc->side && rc->ray_dir.x < 0 &&
	(f.flr_w.x = rc->map.x + 1))
		f.flr_w.y = rc->map.y + rc->wall_x;
	else if (rc->side && rc->ray_dir.y > 0 &&
	(f.flr_w.x = rc->map.x + rc->wall_x))
		f.flr_w.y = rc->map.y;
	else if (rc->side && rc->ray_dir.y < 0 &&
	(f.flr_w.x = rc->map.x + rc->wall_x))
		f.flr_w.y = rc->map.y + 1;
	f.dst_w = rc->perp_wall_dist;
	f.dst_p = 0;
	if (rc->draw_end < 0)
		rc->draw_end = win->wh;
	y = rc->draw_end;
	draw_floor_help(win, x, y, f);
}

void			draw_y_stripe(t_ray_cast *rc, t_data *w, int x, int y)
{
	int		tex_pix;

	while (++y < rc->draw_end)
	{
		rc->delta = y * 256 - w->wh * 128 + rc->line_h * 128;
		rc->tex.y = ((rc->delta * w->th) / rc->line_h) / 256;
		tex_pix = w->th * rc->tex.y + rc->tex.x;
		if (w->check_wall)
		{
			if (!rc->side && rc->ray_dir.x > 0)
				rc->col = w->texture[0][tex_pix];
			else if (!rc->side && rc->ray_dir.x < 0)
				rc->col = w->texture[2][tex_pix];
			else if (rc->side && rc->ray_dir.y > 0)
				rc->col = w->texture[4][tex_pix];
			else if (rc->side && rc->ray_dir.y < 0)
				rc->col = w->texture[5][tex_pix];
		}
		else
			rc->col = w->texture[rc->tex_num][tex_pix];
		if (rc->side == 1)
			rc->col = (rc->col >> 1) & 8355711;
		img_pixel_put(w, x, y, rc->col);
	}
	draw_floor(rc, w, x);
}
