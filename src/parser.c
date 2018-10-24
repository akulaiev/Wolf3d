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

static void	free_and_exit(char *tmp_line, t_parce *res)
{
	free(tmp_line);
	ft_double_free((void**)res->map, res->mh);
	system("leaks wolf3d");
	exit(write(2, "Problem with source_file!\n", 26));
}

static void	check_all_cases(t_read_file rf, t_parce *res, int check_type)
{
	int		i;
	int		tmp;
	char	*l;

	l = rf.tmp_line;
	if (check_type == 1 && ((!ft_isdigit(l[rf.j]) && l[rf.j] != ' ' &&
	l[rf.j] != 'P') || (l[rf.j] == ' ' && (!ft_isdigit(l[rf.j - 1]) &&
	l[rf.j - 1] != 'P')) || ((ft_isdigit(l[rf.j]) || l[rf.j] == 'P') &&
	l[rf.j + 1] != ' ' && l[rf.j + 1] != '\0')))
	{
		res->mh++;
		free_and_exit(l, res);
	}
	if (check_type == 1 && l[rf.j] == 'P')
	{
		if ((res->pos.x || res->pos.y) && (res->mh++))
			free_and_exit(l, res);
		i = rf.j;
		tmp = rf.j;
		while (i && --i)
		{
			if (l[i] == ' ')
				rf.j--;
		}
		res->pos.x = rf.j;
		res->pos.y = res->mh;
		l[tmp] = '0';
	}
	if (check_type == 2 && rf.mw_temp != res->mw)
		free_and_exit(l, res);
	if (check_type == 2 && ft_isdigit(l[0]))
		res->mh++;
	if (check_type == 3)
	{
		while (++rf.j < res->mw)
		{
			if (!res->map[res->mh - 1][rf.j])
				res->map[res->mh - 1][rf.j] = 1;
		}
		if (res->mw < 3 || res->mh < 3 || !res->pos.x || !res->pos.y
		|| res->pos.x >= res->mw - 1 || res->pos.y >= res->mh - 1)
			free_and_exit(l, res);
	}
}

static void	read_file(int fd, t_parce *res)
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
			check_all_cases(rf, res, 1);
			if (ft_isdigit(rf.tmp_line[rf.j]))
			{
				res->map[res->mh][++rf.k] = ft_atoi(&rf.tmp_line[rf.j]);
				if (!res->map[res->mh][rf.k] && (rf.k == 0 || res->mh == 0
				|| rf.k == res->mw - 1))
					res->map[res->mh][rf.k] = 1;
			}
		}
		rf.mw_temp = rf.k + 1;
		check_all_cases(rf, res, 2);
		free(rf.tmp_line);
	}
	check_all_cases(rf, res, 3);
}

void		parser(t_data *win, int fd)
{
	t_parce		res;

	res.pos.x = 0;
	res.pos.y = 0;
	res.mh = 0;
	res.mw = 0;
	read_file(fd, &res);
	int i = -1;
	while (++i < res.mh)
	{
		int j = -1;
		while (++j < res.mw)
			printf("%i", res.map[i][j]);
		printf("\n");
	}
	win->mw = res.mh;
	win->mh = res.mw;
	printf("mw: %i mh: %i\n", win->mw, win->mh);
	exit(0);
	win->pl->pos.x = res.pos.x;
	win->pl->pos.y = res.pos.y;
	win->map = res.map;
}