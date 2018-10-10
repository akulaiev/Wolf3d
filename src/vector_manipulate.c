/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_manipulate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:01:51 by akulaiev          #+#    #+#             */
/*   Updated: 2018/10/08 13:01:53 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	normalize(t_dot *ray)
{
	double	ray_len;

	ray_len = sqrt(ray->x * ray->x + ray->y * ray->y);
	ray->x /= ray_len;
	ray->y /= ray_len;
}

t_dot	vmn(t_dot first, t_dot second)
{
	t_dot	res;

	res.x = first.x - second.x;
	res.y = first.y - second.y;
	return (res);
}

t_dot	vr(t_dot vec, double angle)
{
	double	angle_rad;
	double 	old_x;
	t_dot	res;

	angle_rad = angle * (M_PI / 180);
	old_x = vec.x;
	res.x = vec.x * cos(angle_rad) - vec.y * sin(angle_rad);
	res.y = old_x * sin(angle_rad) + cos(angle_rad);
	return (res);
}

// t_base	get_basis(t_dot vect)
// {
// 	t_dot	tmp;
// 	t_base	res;

// 	tmp.x = vect.x;
// 	tmp.y = vect.y + 0.0001;
// 	tmp.z = vect.z + 0.0002;
// 	res.right_vect = vc(vect, tmp);
// 	normalize(&res.right_vect);
// 	res.up_vect = vc(vect, res.right_vect);
// 	normalize(&res.up_vect);
// 	res.right_vect = vc(vect, res.up_vect);
// 	normalize(&res.right_vect);
// 	res.dir_vect = vect;
// 	return (res);
// }
