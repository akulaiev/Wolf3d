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
	tex_names[0] = ft_strdup("./textures/colorstone.XPM");
	tex_names[1] = ft_strdup("./textures/bluestone.XPM");
	tex_names[2] = ft_strdup("./textures/greystone.XPM");
	tex_names[3] = ft_strdup("./textures/mossy.XPM");
	tex_names[4] = ft_strdup("./textures/purplestone.XPM");
	tex_names[5] = ft_strdup("./textures/redbrick.XPM");
	tex_names[6] = ft_strdup("./textures/wood.XPM");
	tex_names[7] = ft_strdup("./textures/glass.XPM");
	w->texture = (int**)malloc(sizeof(int*) * 8);
	i = -1;
	while (++i < 8)
	{
		w->texture[i] = (int*)mlx_xpm_file_to_image(w->mlx_p,
		tex_names[i], &w->tw, &w->th);
		w->texture[i] = (int*)mlx_get_data_addr(w->texture[i], &bpp, &sl, &e);
		if (!w->texture[i])
			exit(write(2, "Failed to upload texture!\n", 26));
	}
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
	open_win(&win);
	tex_gen(&win);
	raycast(&win);
}
