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

void		tex_gen(t_data *w)
{
	char	**tex_names;
	int		i;
	int		bpp;
	int		sl;
	int		e;

	tex_names = (char**)malloc(sizeof(char*) * 8);
	tex_names[0] = ft_strdup("./my_textures/good_wood.XPM"); // ./original_textures/colorstone.XPM
	tex_names[1] = ft_strdup("./my_textures/colorful_smoke.XPM"); // ./original_textures/bluestone.XPM
	tex_names[2] = ft_strdup("./my_textures/lemons.XPM"); // ./original_textures/greystone.XPM
	tex_names[3] = ft_strdup("./my_textures/flowers.XPM"); // ./original_textures/mossy.XPM
	tex_names[4] = ft_strdup("./my_textures/poked_walls.XPM"); // ./original_textures/purplestone.XPM
	tex_names[5] = ft_strdup("./my_textures/old_bricks.XPM"); // ./original_textures/redbrick.XPM
	tex_names[6] = ft_strdup("./my_textures/wooden_floor.XPM"); // ./original_textures/wood.XPM
	tex_names[7] = ft_strdup("./my_textures/sunset_sky.XPM"); // ./original_textures/glass.XPM
	w->texture = (int**)malloc(sizeof(int*) * 8);
	i = -1;
	while (++i < 8)
	{
		w->texture[i] = (int*)mlx_xpm_file_to_image(w->mlx_p,
		tex_names[i], &w->tw, &w->th);
		if (!w->texture[i])
			exit(write(2, "Failed to upload texture!\n", 26));
		w->texture[i] = (int*)mlx_get_data_addr(w->texture[i], &bpp, &sl, &e);
		
	}
}

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
	parser(&win, fd);
	play.pos.x = 22;
	play.pos.y = 11.5;
	play.dir.x = -1;
	play.dir.y = 0;
	play.cam_plane.x = 0;
	play.cam_plane.y = 0.66;
	win.pl = &play;
	open_win(&win);
	tex_gen(&win);
	raycast(&win);
}
