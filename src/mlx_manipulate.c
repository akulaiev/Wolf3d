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
	exit(0);
}

int			key_react(int keycode, void *param)
{
	t_data		*p;
	t_player	*play;

	p = (t_data*)param;
	play = p->pl;
	// printf("%i\n", keycode);
	if (keycode == 53)
		exit(0);
	else if (keycode == 126) //up arrow
	{
		mlx_clear_window(p->mlx_p, p->mlx_nw);
		if (!p->world_map[(int)(play->pos.x + play->dir.x * p->mv_sp)][(int)play->pos.y])
			play->pos.x += play->dir.x * p->mv_sp;
		if (!p->world_map[(int)play->pos.x][(int)(play->pos.y + play->dir.y * p->mv_sp)])
			play->pos.y += play->dir.y * p->mv_sp;
		printf("up: %f\n", play->pos.x);
		raycast(p);
	}
	else if (keycode == 125) //down arrow
	{
		mlx_clear_window(p->mlx_p, p->mlx_nw);
		if (!p->world_map[(int)(play->pos.x - play->dir.x * p->mv_sp)][(int)play->pos.y])
			play->pos.x -= play->dir.x * p->mv_sp;
		if (!p->world_map[(int)play->pos.x][(int)(play->pos.y - play->dir.y * p->mv_sp)])
			play->pos.y -= play->dir.y * p->mv_sp;
		printf("down: %f\n", play->pos.x);
		raycast(p);
	}
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
