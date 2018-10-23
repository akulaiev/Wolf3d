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

static void	free_and_exit(char *tmp_line, t_parce *res)
{
	printf("%i\n", res->mh);
	free(tmp_line);
	ft_double_free((void**)res->map, res->mh);
	system("leaks wolf3d");
	exit(write(2, "Problem with source_file!\n", 26));
}

static void	check_all_cases(char *l, int j, t_parce *res, int mw_temp, int check_type)
{
	int		i;
	int		tmp;

	if (check_type == 1 && ((!ft_isdigit(l[j]) && l[j] != ' ' && l[j] != 'P') ||
	(l[j] == ' ' && (!ft_isdigit(l[j - 1]) && l[j - 1] != 'P')) ||
	((ft_isdigit(l[j]) || l[j] == 'P') && l[j + 1] != ' ' && l[j + 1] != '\0')))
		free_and_exit(l, res);
	if (check_type == 1 && l[j] == 'P')
	{
		if (res->pos.x || res->pos.y)
			free_and_exit(l, res);
		i = j;
		tmp = j;
		while (i && --i)
		{
			if (l[i] == ' ')
				j--;
		}
		res->pos.x = j;
		res->pos.y = res->mh;
		l[tmp] = '0';
	}
	if (check_type == 2 && mw_temp != res->mw)
		free_and_exit(l, res);
	if (check_type == 2 && ft_isdigit(l[0]))
		res->mh++;
	if (check_type == 3)
	{
		while (++j < res->mw)
		{
			if (!res->map[res->mh - 1][j])
				res->map[res->mh - 1][j] = 1;
		}
		if (res->mw < 3 || res->mh < 3 || !res->pos.x || !res->pos.y
		|| res->pos.x >= res->mw - 1 || res->pos.y >= res->mh - 1)
			free_and_exit(l, res);
	}
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
			check_all_cases(tmp_line, j, res, mw_temp, 1);
			if (ft_isdigit(tmp_line[j]))
			{
				res->map[res->mh][++k] = ft_atoi(&tmp_line[j]);
				if (!res->map[res->mh][k] && (k == 0 || res->mh == 0
				|| k == res->mw - 1))
					res->map[res->mh][k] = 1;
			}
		}
		mw_temp = k + 1;
		check_all_cases(tmp_line, j, res, mw_temp, 2);
		free(tmp_line);
	}
	check_all_cases(NULL, -1, res, 0, 3);
}

void		parser(t_data *win, int fd)
{
	t_parce		res;

	res.pos.x = 0;
	res.pos.y = 0;
	read_file(fd, &res);
	int i = -1;
	while (++i < res.mh)
	{
		int j = -1;
		while (++j < res.mw)
			printf("%i", res.map[i][j]);
		printf("\n");
	}
	printf("pos.x: %f pos.y: %f\n", res.pos.x, res.pos.y);
	ft_double_free((void**)res.map, res.mh);
	system("leaks wolf3d");
	exit(0);
	win->mh = res.mh;
	win->mw = res.mw;
	win->pl->pos.x = res.pos.x;
	win->pl->pos.y = res.pos.y;
	win->world_map = res.map;
}