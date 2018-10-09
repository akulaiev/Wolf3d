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

static int	exit_x(void)
{
	exit(0);
}

int			key_react(int keycode, void *param)
{
	param = NULL;
	if (keycode == 53)
		exit(0);
	return (0);
}

void		open_win(t_data *win)
{
	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->ww, win->wh, "Test");
	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wh);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	mlx_hook(win->mlx_nw, 17, 1L << 17, exit_x, (void*)win);
}

void		img_pixel_put(t_data *win, int x, int y, int col)
{
	if (x < win->ww && y < win->wh && x >= 0 && y >= 0)
		*(int*)(win->img_ptr + (x * (win->bits_per_pixel >> 3) +
		y * win->size_line)) = col;
}

void	raycast(t_player pl, t_data *win, int world_map[MW][MH])
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
	while (++x < win->ww)
	{
		x_norm = 2 * x / (double)win->ww - 1;
		ray_dir = va(vm(pl.cam_plane, x_norm), pl.dir);
		map_x = (int)pl.pos.x;
		map_y = (int)pl.pos.y;

		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		hit = 0;
		if (ray_dir.x < 0 && (step_x = -1))
			side_dist.x = (pl.pos.x - map_x) * delta_dist.x;
		if (ray_dir.x >= 0 && (step_x = 1))
			side_dist.x = (map_x + 1 - pl.pos.x) * delta_dist.x;
		if (ray_dir.y < 0 && (step_y = -1))
			side_dist.y = (pl.pos.y - map_y) * delta_dist.y;
		if (ray_dir.y >= 0 && (step_y = 1))
			side_dist.y = (map_y + 1 - pl.pos.y) * delta_dist.y;
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
			if (world_map[map_x][map_y] > 0)
				hit = 1;
		}
		if (!side)
			perp_wall_dist = (map_x - pl.pos.x + (1 - step_x) / 2) / ray_dir.x;
		else
			perp_wall_dist = (map_y - pl.pos.y + (1 - step_y) / 2) / ray_dir.y;
		line_h = (int)(win->wh / perp_wall_dist);
		draw_start = -line_h / 2 + win->wh / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + win->wh / 2;
		if(draw_end >= win->wh)
			draw_end = win->wh - 1;
		if (world_map[map_x][map_y] == 1)
			col.integer = 0xff0000; //red
		if (world_map[map_x][map_y] == 2)
			col.integer = 0x00ff00; //green
		if (world_map[map_x][map_y] == 3)
			col.integer = 0x0000ff; //blue
		if (world_map[map_x][map_y] == 4)
			col.integer = 0xffffff; //white
		if (world_map[map_x][map_y] == 5)
			col.integer = 0xffff00; //yellow
		if (side == 1)
			col.integer /= 2;
		breth_vertical(x, draw_start, draw_end, col, win);
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	mlx_loop(win->mlx_p);
}

int		main(void)
{
	int world_map[MW][MH]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	t_player	pl;
	t_data		win;
	// double		time = 0;
	// double		old_time = 0;

	pl.pos.x = 22;
	pl.pos.y = 12;
	pl.dir.x = -1;
	pl.dir.y = 0;
	pl.cam_plane.x = 0;
	pl.cam_plane.y = 0.65;
	win.ww = 800;
	win.wh = 512;
	open_win(&win);
	raycast(pl, &win, world_map);
}
