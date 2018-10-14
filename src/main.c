/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:16:54 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/08 11:16:55 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	raycast(t_data *win)
{
	int		x;
	int		y;
	double	x_norm;
	t_dot	ray_dir;
	t_dot_i	map;
	t_dot	side_dist;
	t_dot	delta_dist;
	double	perp_wall_dist;
	t_dot_i	step;
	int		hit;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	t_col	col;
	int		tex_num;
	double	wall_x;
	t_dot_i	tex;
	int		d;

	x = -1;
	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wh);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	while (++x < win->ww)
	{
		x_norm = 2 * x / (double)win->ww - 1;
		ray_dir = va(vm(win->pl->cam_plane, x_norm), win->pl->dir);
		map.x = (int)win->pl->pos.x;
		map.y = (int)win->pl->pos.y;
		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		hit = 0;
		if (ray_dir.x < 0 && (step.x = -1))
			side_dist.x = (win->pl->pos.x - map.x) * delta_dist.x;
		if (ray_dir.x >= 0 && (step.x = 1))
			side_dist.x = (map.x + 1 - win->pl->pos.x) * delta_dist.x;
		if (ray_dir.y < 0 && (step.y = -1))
			side_dist.y = (win->pl->pos.y - map.y) * delta_dist.y;
		if (ray_dir.y >= 0 && (step.y = 1))
			side_dist.y = (map.y + 1 - win->pl->pos.y) * delta_dist.y;
		while (!hit)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (win->world_map[map.x][map.y] > 0)
				hit = 1;
		}
		if (!side)
			perp_wall_dist = (map.x - win->pl->pos.x + (1 - step.x) / 2) / ray_dir.x;
		else
			perp_wall_dist = (map.y - win->pl->pos.y + (1 - step.y) / 2) / ray_dir.y;
		line_h = (int)(win->wh / perp_wall_dist);
		draw_start = -line_h / 2 + win->wh / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + win->wh / 2;
		if(draw_end >= win->wh)
			draw_end = win->wh - 1;

		tex_num = win->world_map[map.x][map.y] - 1;
		if (!side)
			wall_x = win->pl->pos.y + perp_wall_dist * ray_dir.y;
		else
			wall_x = win->pl->pos.x + perp_wall_dist * ray_dir.x;
		wall_x -= floor(wall_x);
		tex.x = (int)(wall_x * (double)TW);
		if ((!side && ray_dir.x > 0) || (side == 1 && ray_dir.y < 0))
			tex.x = TW - tex.x - 1;
		y = draw_start - 1;
		while (++y < draw_end)
		{
			d = y * 256 - MH * 128 + line_h * 128;
			tex.y = ((d * TH) / line_h) / 256;
			col = win->texture[tex_num][TH * tex.x + tex.y];
			if (side == 1)
			{
				col.struct_col.r /= 2;
				col.struct_col.g /= 2;
				col.struct_col.b /= 2;
			}
			img_pixel_put(win, x, y, col.integer);
		}
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	mlx_loop(win->mlx_p);
}

t_col		**tex_gen(void)
{
	t_col 	**tex;
	int		x;
	int		y;

	tex = (t_col**)malloc(sizeof(t_col*) * 8);
	int i = -1;
	while (++i < 8)
		tex[i] = (t_col*)malloc(sizeof(t_col) * (TW * TH));
	x = -1;
	while (++x < TW)
	{
		y = -1;
		while (++y < TH)
		{
			int xorcolor = (x * 256 / TW) ^ (y * 256 / TH);
			// int xcolor = x * 256 / TW;
			int ycolor = y * 256 / TH;
			int xycolor = y * 128 / TH + x * 128 / TW;
			tex[0][TW * y + x].integer = 0xff0000 * (x != y && x != TW - y); //flat red texture with black cross
			tex[1][TW * y + x].integer = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			tex[2][TW * y + x].integer = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			tex[3][TW * y + x].integer = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			tex[4][TW * y + x].integer = 256 * xorcolor; //xor green
			tex[5][TW * y + x].integer = 0xC00000 * (x % 16 && y % 16); //red bricks
			tex[6][TW * y + x].integer = 65536 * ycolor; //red gradient
			tex[7][TW * y + x].integer = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
	return (tex);
}

int		main(void)
{
	t_data		win;
	t_player	play;
	int			map[MW][MH] = 
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,1},
		{1,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,1},
		{1,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
		{1,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,1},
		{1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
		{1,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
		{1,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
		{1,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,1},
		{1,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,1},
		{1,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,1},
		{1,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,1},
		{1,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,1},
		{1,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	win.world_map = (int**)malloc(sizeof(int*) * MW);
	int i = -1;
	while (++i < MW)
	{
		int j = -1;
		win.world_map[i] = (int*)malloc(sizeof(int) * MH);
		while (++j < MH)
			win.world_map[i][j] = map[i][j];
	}
	play.pos.x = 22;
	play.pos.y = 11.5;
	play.dir.x = -1;
	play.dir.y = 0;
	play.cam_plane.x = 0;
	play.cam_plane.y = 0.66;
	win.pl = &play;
	win.ww = 800;
	win.wh = 512;
	win.texture = tex_gen();
	open_win(&win);
	raycast(&win);
}
