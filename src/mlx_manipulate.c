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

int			exit_x(void)
{
	system("leaks wolf3d");
	exit(0);
}

int		key(t_data *win)
{
	if (win->keys->up == 1 || win->keys->down == 1)
		move(win, win->pl);
	if (win->keys->left == 1 || win->keys->right == 1)
		turn_around(win, win->pl);
	mlx_destroy_image(win->mlx_p, win->mlx_img);
	raycast(win);
	return (0);
}

void		open_win(t_data *win)
{
	t_key		k;

	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->ww, win->wh, "Test");
	k.up = 0;
	k.down = 0;
	k.left = 0;
	k.right = 0;
	win->keys = &k;
	mlx_hook(win->mlx_nw, 2, 5, key_down, (void*)win);
	mlx_hook(win->mlx_nw, 3, 5, key_up, (void*)win);
	mlx_loop_hook(win->mlx_p, key, win);
	mlx_hook(win->mlx_nw, 17, 1L << 17, exit_x, (void*)win);
}

void		img_pixel_put(t_data *win, int x, int y, int col)
{
	if (x < win->ww && y < win->wh && x >= 0 && y >= 0)
		*(int*)(win->img_ptr + (x * (win->bits_per_pixel >> 3) +
		y * win->size_line)) = col;
}
