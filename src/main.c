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

int		main(int argc, char **argv)
{
	t_data		win;
	t_player	play;
	int			fd;

	if (argc != 2)
		return (write(2, "usage: ./wolf3d source_file\n", 28));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (write(2, "Source file doesn't exist!\n", 27));
	win.pl = &play;
	win.ww = 800;
	win.wh = 512;
	play.dir.x = -1;
	play.dir.y = 0;
	play.cam_plane.x = 0;
	play.cam_plane.y = 0.66;
	win.pl = &play;
	win.tex_set = 0;
	win.check_wall = 0;
	parser(&win, fd);
	open_win(&win);
	tex_gen(&win);
	raycast(&win);
	mlx_loop(win.mlx_p);
}
