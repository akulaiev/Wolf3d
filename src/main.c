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
	double	x_norm;
	t_dot	ray_dir;
	int		map_x;
	int		map_y;
	t_dot	side_dist;
	t_dot	delta_dist;
	double	perp_wall_dist;
	int 	step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	t_col	col;

	x = -1;
	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wh);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	while (++x < win->ww)
	{
		x_norm = 2 * x / (double)win->ww - 1;
		ray_dir = va(vm(win->pl->cam_plane, x_norm), win->pl->dir);
		map_x = (int)win->pl->pos.x;
		map_y = (int)win->pl->pos.y;
		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		hit = 0;
		if (ray_dir.x < 0 && (step_x = -1))
			side_dist.x = (win->pl->pos.x - map_x) * delta_dist.x;
		if (ray_dir.x >= 0 && (step_x = 1))
			side_dist.x = (map_x + 1 - win->pl->pos.x) * delta_dist.x;
		if (ray_dir.y < 0 && (step_y = -1))
			side_dist.y = (win->pl->pos.y - map_y) * delta_dist.y;
		if (ray_dir.y >= 0 && (step_y = 1))
			side_dist.y = (map_y + 1 - win->pl->pos.y) * delta_dist.y;
		while (!hit)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_y += step_y;
				side = 1;
			}
			if (win->world_map[map_x][map_y] > 0)
				hit = 1;
		}
		if (!side)
			perp_wall_dist = (map_x - win->pl->pos.x + (1 - step_x) / 2) / ray_dir.x;
		else
			perp_wall_dist = (map_y - win->pl->pos.y + (1 - step_y) / 2) / ray_dir.y;
		line_h = (int)((double)win->wh / perp_wall_dist);
		draw_start = -line_h / 2 + win->wh / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + win->wh / 2;
		if(draw_end >= win->wh)
			draw_end = win->wh - 1;
		if (win->world_map[map_x][map_y] == 1)
			col.integer = 0xff0000; //red
		if (win->world_map[map_x][map_y] == 2)
			col.integer = 0x00ff00; //green
		if (win->world_map[map_x][map_y] == 3)
			col.integer = 0x0000ff; //blue
		if (win->world_map[map_x][map_y] == 4)
			col.integer = 0xffffff; //white
		if (win->world_map[map_x][map_y] == 5)
			col.integer = 0xffff00; //yellow
		if (side == 1)
			col.integer /= 2;
		breth_vertical(x, draw_start, draw_end, col, win);
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	mlx_loop(win->mlx_p);
}

int		**tex_gen(void)
{
	int 	**tex;
	int		x;
	int		y;

	tex = (int**)malloc(sizeof(int*) * 8);
	int i = -1;
	while (++i < 8)
		tex[i] = (int*)malloc(sizeof(int) * (TW * TH));
	x = -1;
	while (++x < TW)
	{
		y = -1;
		while (++y < TH)
		{
			int xorcolor = (x * 256 / TW) ^ (y * 256 / TH);
			//int xcolor = x * 256 / TW;
			int ycolor = y * 256 / TH;
			int xycolor = y * 128 / TH + x * 128 / TW;
			tex[0][TW * y + x] = 65536 * 254 * (x != y && x != TW - y); //flat red texture with black cross
			tex[1][TW * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			tex[2][TW * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			tex[3][TW * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			tex[4][TW * y + x] = 256 * xorcolor; //xor green
			tex[5][TW * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			tex[6][TW * y + x] = 65536 * ycolor; //red gradient
			tex[7][TW * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
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
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
		{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
		{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
		{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
		{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
		{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
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
	play.pos.y = 12;
	play.dir.x = -1;
	play.dir.y = 0;
	play.cam_plane.x = 0;
	play.cam_plane.y = 0.66;
	win.pl = &play;
	win.ww = 800;
	win.wh = 512;

	int	**texture = tex_gen();
	open_win(&win);
	raycast(&win);
}
