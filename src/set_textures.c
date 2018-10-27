/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:44:47 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/25 16:44:49 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static char		**set_one(t_data *w)
{
	char	**tex_names;

	w->tex_n = 6;
	tex_names = (char**)malloc(sizeof(char*) * w->tex_n + 2);
	tex_names[0] = ft_strdup("./original_textures/redbrick.XPM");
	tex_names[1] = ft_strdup("./original_textures/clay.XPM");
	tex_names[2] = ft_strdup("./original_textures/greystone.XPM");
	tex_names[3] = ft_strdup("./original_textures/mossy.XPM");
	tex_names[4] = ft_strdup("./original_textures/bookshelf.XPM");
	tex_names[5] = ft_strdup("./original_textures/colorstone.XPM");
	tex_names[6] = ft_strdup("./original_textures/wood.XPM");
	tex_names[7] = ft_strdup("./original_textures/iron_block.XPM");
	return (tex_names);
}

static char		**set_two(t_data *w)
{
	char	**tex_names;

	w->tex_n = 6;
	tex_names = (char**)malloc(sizeof(char*) * w->tex_n + 2);
	tex_names[0] = ft_strdup("./my_textures/good_wood.XPM");
	tex_names[1] = ft_strdup("./my_textures/colorful_smoke.XPM");
	tex_names[2] = ft_strdup("./my_textures/lemons.XPM");
	tex_names[3] = ft_strdup("./my_textures/flowers.XPM");
	tex_names[4] = ft_strdup("./my_textures/poked_walls.XPM");
	tex_names[5] = ft_strdup("./my_textures/old_bricks.XPM");
	tex_names[6] = ft_strdup("./my_textures/wooden_floor.XPM");
	tex_names[7] = ft_strdup("./my_textures/sunset_sky.XPM");
	return (tex_names);
}

void		tex_gen(t_data *w)
{
	char	**tex_names;
	int		i;
	int		bpp;
	int		sl;
	int		e;

	if (w->tex_set == 0)
		tex_names = set_one(w);
	if (w->tex_set == 1)
		tex_names = set_two(w);
	i = -1;
	// if (w->tex_n)
	// 	ft_double_free((void**)w->texture, w->tex_n);
	w->texture = (int**)malloc(sizeof(int*) * w->tex_n + 2);
	while (++i < w->tex_n + 2)
	{
		w->texture[i] = (int*)mlx_xpm_file_to_image(w->mlx_p,
		tex_names[i], &w->tw, &w->th);
		if (!w->texture[i])
		{
			ft_double_free((void**)tex_names, i);
			exit(write(2, "Failed to upload texture!\n", 26));
		}
		w->texture[i] = (int*)mlx_get_data_addr(w->texture[i], &bpp, &sl, &e);
	}
	ft_double_free((void**)tex_names, w->tex_n + 2);
}
