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
	tex_names[0] = ft_strdup("./fancy_tex/marble_dark.XPM");
	tex_names[1] = ft_strdup("./fancy_tex/marbel.XPM");
	tex_names[2] = ft_strdup("./fancy_tex/plaster.XPM");
	tex_names[3] = ft_strdup("./fancy_tex/pink_tiles.XPM");
	tex_names[4] = ft_strdup("./fancy_tex/poked_walls.XPM");
	tex_names[5] = ft_strdup("./fancy_tex/blue_paint.XPM");
	tex_names[6] = ft_strdup("./fancy_tex/white_wood.XPM");
	tex_names[7] = ft_strdup("./fancy_tex/marbel_white.XPM");
	return (tex_names);
}

void			tex_gen(t_data *w)
{
	t_set_tex		t;

	if (w->tex_set == 0)
		t.tn = set_one(w);
	if (w->tex_set == 1)
		t.tn = set_two(w);
	t.i = -1;
	if (w->texture)
		ft_double_free((void**)w->texture, w->tex_n + 2);
	w->texture = (int**)malloc(sizeof(int*) * w->tex_n + 2);
	while (++t.i < w->tex_n + 2)
	{
		w->texture[t.i] = (int*)mlx_xpm_file_to_image(w->mlx_p,
		t.tn[t.i], &w->tw, &w->th);
		if (!w->texture[t.i])
		{
			ft_double_free((void**)t.tn, w->tex_n + 2);
			exit(write(2, "Failed to upload texture!\n", 26));
		}
		w->texture[t.i] = (int*)mlx_get_data_addr(w->texture[t.i],
		&t.bpp, &t.sl, &t.e);
	}
	ft_double_free((void**)t.tn, w->tex_n + 2);
}
