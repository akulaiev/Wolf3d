/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:52:33 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/19 13:52:35 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static int		**realloc_2d(t_parce *res, char *tmp_line)
{
	int		**new_mem;
	int		i;
	int		j;
	int		first_time;

	first_time = 0;
	if (!res->mw)
	{
		i = -1;
		while (tmp_line[++i])
		{
			if (ft_isdigit(tmp_line[i]) && (tmp_line[i + 1] == ' ' ||
			tmp_line[i + 1] == '\0'))
				res->mw++;
		}
		first_time = 1;
	}
	new_mem = (int**)malloc(sizeof(int*) * res->mh + 1);
	i = -1;
	while (++i <= res->mh + first_time)
	{
		new_mem[i] = (int*)malloc(sizeof(int) * res->mw);
		j = -1;
		while (++j < res->mw && !first_time && i < res->mh)
			new_mem[i][j] = res->map[i][j];
	}
	if (!first_time)
		ft_double_free((void**)res->map, res->mh);
	return (new_mem);
}

static void	read_file(int fd, t_parce *res)
{
	char	*tmp_line;
	int		j;
	int		k;
	int		mw_temp;

	tmp_line = NULL;
	res->mh = 0;
	res->mw = 0;
	while (get_next_line(fd, &tmp_line))
	{
		res->map = realloc_2d(res, tmp_line);
		j = -1;
		k = -1;
		while (tmp_line[++j])
		{
			if ((!ft_isdigit(tmp_line[j]) && tmp_line[j] != ' ')
			|| (ft_isdigit(tmp_line[j]) && tmp_line[j + 1] != ' ' &&
			tmp_line[j + 1] != '\0'))
			{
				free(tmp_line);
				ft_double_free((void**)res->map, res->mh);
				exit(write(2, "Problem with source_file!\n", 26));
			}
			if (ft_isdigit(tmp_line[j]))
			{
				res->map[res->mh][++k] = ft_atoi(&tmp_line[j]);
				if (!res->map[res->mh][k] && (k == 0 || res->mh == 1
				|| k == res->mw - 1))
					res->map[res->mh][k] = 1;
			}
		}
		mw_temp = k + 1;
		if (mw_temp != res->mw)
		{
			free(tmp_line);
			ft_double_free((void**)res->map, res->mh);
			exit(write(2, "Problem with source_file!\n", 26));
		}
		res->mh++;
	}
	// j = -1;
	// while (++j < res->mw && !res->map[res->mh - 1][j])
	// 	res->map[res->mh - 1][j] = 1;
}

void		parser(t_data *win, int fd)
{
	t_parce		res;

	read_file(fd, &res);
	int i = -1;
	while (++i < res.mh)
	{
		int j = -1;
		while (++j < res.mw)
			printf("%i", res.map[i][j]);
		printf("\n");
	}
	exit(0);
	win->mh = res.mh;
	win->mw = res.mw;
	win->world_map = res.map;
}