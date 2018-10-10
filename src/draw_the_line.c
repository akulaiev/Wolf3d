/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_the_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:40:43 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/09 12:40:45 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"
#include <stdio.h>

static void		pix_put_y(t_breth brth, t_col col, t_data *win)
{
	brth.len_y = brth.leng_y;
	brth.d1 = brth.dx2 - brth.leng_y;
	while (brth.leng_y--)
	{
		img_pixel_put(win, brth.x, brth.y, col.integer);
		if (brth.d1 > 0)
			brth.d1 -= brth.dy2;
		brth.d1 += brth.dx2;
		brth.y += brth.y_inc;
	}
}

void			breth_vertical(int x, int y_start, int y_end, t_col col, t_data *win)
{
	t_breth		brth;

	brth.dx = x;
	brth.dy = y_end - y_start;
	brth.leng_x = abs(brth.dx);
	brth.leng_y = abs(brth.dy);
	brth.y_inc = (brth.dy < 0) ? -1 : 1;
	brth.length = fmax((float)brth.leng_x, (float)brth.leng_y) + 1;
	brth.x = x;
	brth.y = y_start;
	brth.dx2 = brth.leng_x << 1;
	brth.dy2 = brth.leng_y << 1;
	pix_put_y(brth, col, win);
}

// static void		pix_put_x(t_breth brth, t_col col, t_data *win)
// {
// 	brth.len_x = brth.leng_x;
// 	brth.d1 = brth.dy2 - brth.leng_x;
// 	while (brth.leng_x--)
// 	{
// 		img_pixel_put(win, brth.x, brth.y, col.integer);
// 		if (brth.d1 > 0)
// 			brth.d1 -= brth.dx2;
// 		brth.d1 += brth.dy2;
// 		brth.x += brth.x_inc;
// 	}
// }

// void			breth_horizontal(int y, int x_start, int x_end, t_col col, t_data *win)
// {
// 	t_breth		brth;

// 	brth.dx = x_end - x_start;
// 	brth.dy = y;
// 	brth.leng_x = abs(brth.dx);
// 	brth.leng_y = abs(brth.dy);
// 	brth.x_inc = (brth.dx < 0) ? -1 : 1;
// 	brth.length = fmax((float)brth.leng_x, (float)brth.leng_y) + 1;
// 	brth.x = x_start;
// 	brth.y = y;
// 	brth.dx2 = brth.leng_x << 1;
// 	brth.dy2 = brth.leng_y << 1;
// 	pix_put_x(brth, col, win);
// }
