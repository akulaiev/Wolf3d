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

static int		**realloc_2d(t_parce *res, char *l, int first_time, int i)
{
	int		**new_mem;
	int		j;

	if (!res->mw)
	{
		while (l[++i])
		{
			if (ft_isdigit(l[i]) && (l[i + 1] == ' ' || l[i + 1] == '\0'))
				res->mw++;
		}
		first_time = 1;
	}
	new_mem = (int**)malloc(sizeof(int*) * res->mh + 1);
	i = -1;
	while (++i <= res->mh + first_time)
	{
		new_mem[i] = (int*)malloc(sizeof(int) * res->mw);
		if (first_time)
			return (new_mem);
		j = -1;
		while (++j < res->mw && i < res->mh)
			new_mem[i][j] = res->map[i][j];
	}
	ft_double_free((void**)res->map, res->mh);
	return (new_mem);
}

static void		read_file(int fd, t_parce *res)
{
	t_read_file		rf;

	rf.tmp_line = NULL;
	while (get_next_line(fd, &rf.tmp_line))
	{
		res->map = realloc_2d(res, rf.tmp_line, 0, -1);
		rf.j = -1;
		rf.k = -1;
		while (rf.tmp_line[++rf.j])
		{
			check_case_first(rf, res);
			if (ft_isdigit(rf.tmp_line[rf.j]))
			{
				res->map[res->mh][++rf.k] = ft_atoi(&rf.tmp_line[rf.j]);
				if (!res->map[res->mh][rf.k] && (rf.k == 0 || res->mh == 0
				|| rf.k == res->mw - 1))
					res->map[res->mh][rf.k] = 1;
			}
		}
		rf.mw_temp = rf.k + 1;
		check_other_cases(rf, res, 2);
		free(rf.tmp_line);
	}
	check_other_cases(rf, res, 3);
}

void			parser(t_data *win, int fd)
{
	t_parce		res;

	res.pos.x = 0;
	res.pos.y = 0;
	res.mh = 0;
	res.mw = 0;
	read_file(fd, &res);
	win->mw = res.mh;
	win->mh = res.mw;
	win->pl->pos.x = res.pos.y + 0.5;
	win->pl->pos.y = res.pos.x + 0.5;
	win->map = res.map;
}
