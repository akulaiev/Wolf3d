/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:21:11 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/16 17:21:13 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void		get_initial_params(t_ray_cast *rc, t_data *win, int x)
{
	rc->x_norm = 2 * x / (double)win->ww - 1;
	rc->ray_dir = va(vm(win->pl->cam_plane, rc->x_norm), win->pl->dir);
	rc->map.x = (int)win->pl->pos.x;
	rc->map.y = (int)win->pl->pos.y;
	rc->delta_dist.x = sqrt(1 + (rc->ray_dir.y * rc->ray_dir.y) /
	(rc->ray_dir.x * rc->ray_dir.x));
	rc->delta_dist.y = sqrt(1 + (rc->ray_dir.x * rc->ray_dir.x) /
	(rc->ray_dir.y * rc->ray_dir.y));
	if (rc->ray_dir.x < 0 && (rc->step.x = -1))
		rc->side_dist.x = (win->pl->pos.x - rc->map.x) * rc->delta_dist.x;
	if (rc->ray_dir.x >= 0 && (rc->step.x = 1))
		rc->side_dist.x = (rc->map.x + 1 - win->pl->pos.x) * rc->delta_dist.x;
	if (rc->ray_dir.y < 0 && (rc->step.y = -1))
		rc->side_dist.y = (win->pl->pos.y - rc->map.y) * rc->delta_dist.y;
	if (rc->ray_dir.y >= 0 && (rc->step.y = 1))
		rc->side_dist.y = (rc->map.y + 1 - win->pl->pos.y) * rc->delta_dist.y;
}

static void		get_perp_wall(t_ray_cast *rc, t_data *win, int hit)
{
	while (!hit)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map.y += rc->step.y;
			rc->side = 1;
		}
		if (win->world_map[rc->map.x][rc->map.y] > 0)
			hit = 1;
	}
	if (!rc->side)
		rc->perp_wall_dist = (rc->map.x - win->pl->pos.x + (1 - rc->step.x) / 2)
		/ rc->ray_dir.x;
	else
		rc->perp_wall_dist = (rc->map.y - win->pl->pos.y + (1 - rc->step.y) / 2)
		/ rc->ray_dir.y;
}

static void		get_textures_params(t_ray_cast *rc, t_data *win)
{
	rc->line_h = (int)(win->wh / rc->perp_wall_dist);
	rc->draw_start = -rc->line_h / 2 + win->wh / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_h / 2 + win->wh / 2;
	if (rc->draw_end >= win->wh)
		rc->draw_end = win->wh - 1;
	rc->tex_num = win->world_map[rc->map.x][rc->map.y] - 1;
	if (!rc->side)
		rc->wall_x = win->pl->pos.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		rc->wall_x = win->pl->pos.x + rc->perp_wall_dist * rc->ray_dir.x;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex.x = (int)(rc->wall_x * (double)win->tw);
	if ((!rc->side && rc->ray_dir.x > 0) ||
	(rc->side == 1 && rc->ray_dir.y < 0))
		rc->tex.x = win->tw - rc->tex.x - 1;
}

void			raycast(t_data *win)
{
	int				x;
	int				y;
	t_ray_cast		rc;

	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wh);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	x = -1;
	while (++x < win->ww)
	{
		get_initial_params(&rc, win, x);
		get_perp_wall(&rc, win, 0);
		get_textures_params(&rc, win);
		y = rc.draw_start - 1;
		draw_y_stripe(&rc, win, x, y);
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	mlx_loop(win->mlx_p);
}
