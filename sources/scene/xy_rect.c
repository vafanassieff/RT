/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:23 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/22 14:15:38 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_xy_rect	*new_xy_rect(double x0, double x1, double y0, double y1, double k)
{
	t_xy_rect	*r;

	if(!(r = malloc(sizeof(t_xy_rect))))
		return (NULL);
	r->x0 = x0;
	r->x1 = x1;
	r->y0 = y0;
	r->y1 = y1;
	r->k = k;
	return (r);
}

BOOL	hit_xy_rect(void *obj, const t_ray ray, const double t[2], t_hit *param)
{
	t_xy_rect	*r;
	double		tbis;
	double		x;
	double		y;

	r = (t_xy_rect*)obj;
	tbis = ((r->k - ray.orig.z) / ray.dir.z);
	if (tbis < t[0] || tbis > t[1])
		return (FALSE);
	x = ray.orig.x + tbis * ray.dir.x;
	y = ray.orig.y + tbis * ray.dir.y;
	if (x < r->x0 || x > r->x1 || y < r->y0 || y > r->y1)
		return (FALSE);
	param->t = tbis;
	param->pos = ray_point_at(ray, param->t);
	param->normal = v3_(0.0, 0.0, 1.0);
	return (TRUE);
}
