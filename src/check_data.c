/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:47:55 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/25 16:48:00 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void	free_and_exit(char *tmp_line, t_parce *res)
{
	if (tmp_line && *tmp_line)
		free(tmp_line);
	if (res->mh > 0)
	{
		// if (tmp_line[0])
		res->mh++;
		ft_double_free((void**)res->map, res->mh);
	}
	system("leaks wolf3d");
	exit(write(2, "Problem with source_file!\n", 26));
}

void		check_case_first(t_read_file rf, t_parce *res)
{
	int		i;
	int		tmp;
	char	*l;

	l = rf.tmp_line;
	if ((!ft_isdigit(l[rf.j]) && l[rf.j] != ' ' &&
	l[rf.j] != 'P') || (l[rf.j] == ' ' && (!ft_isdigit(l[rf.j - 1]) &&
	l[rf.j - 1] != 'P')) || ((ft_isdigit(l[rf.j]) || l[rf.j] == 'P') &&
	l[rf.j + 1] != ' ' && l[rf.j + 1] != '\0'))
		free_and_exit(l, res);
	if (l[rf.j] == 'P')
	{
		if (res->pos.x || res->pos.y || rf.j == 0)
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
}

void		check_other_cases(t_read_file rf, t_parce *res, int check_type)
{
	char	*l;

	l = rf.tmp_line;
	if (check_type == 2 && rf.mw_temp != res->mw)
		free_and_exit(l, res);
	if (check_type == 2 && ft_isdigit(l[0]))
		res->mh++;
	if (check_type == 3)
	{
		rf.j = -1;
		while (++rf.j < res->mw)
		{
			if (!res->map[res->mh - 1][rf.j])
				res->map[res->mh - 1][rf.j] = 1;
		}
		if (res->mw < 3 || res->mh < 3 || !res->pos.x || !res->pos.y
		|| res->pos.x >= res->mw - 1 || res->pos.y >= res->mh - 1)
		{
			res->mh--;
			printf("here\n");
			free_and_exit(l, res);
		}
	}
}
