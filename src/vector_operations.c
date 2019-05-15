/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:01:58 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/08 13:02:00 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_dot	va(t_dot first, t_dot second)
{
	t_dot	res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	return (res);
}

t_dot	vm(t_dot first, double val)
{
	t_dot	res;

	res.x = first.x * val;
	res.y = first.y * val;
	return (res);
}

t_dot	vd(t_dot first, double val)
{
	t_dot	res;

	res.x = first.x / val;
	res.y = first.y / val;
	return (res);
}

double	vs(t_dot first, t_dot second)
{
	double	res;

	res = first.x * second.x + first.y * second.y;
	return (res);
}
