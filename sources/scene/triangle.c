/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:42:31 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/07 15:55:51 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_triangle	*new_triangle(t_vec3 verterx, t_vec3 normale, t_vec3 corner1, t_vec3	corne2)
{
	t_triangle *t;

	if(!(t = malloc(sizeof(t_triangle))))
		return (0);
	t->vertex = vertex;
	t->normale = normale;
	t->corner1 = corner1;
	t->corner2 = corner2;
	return (t);
}
BOOL	normal_triangle(const t_triangle *t, const t_ray ray, const double sol, t_hit *param)
{
	param->t = sol;
	param->pos = ray_point_at(ray, param->t);
	if (v3_dot_double_(ray.dir, t->normale) < 0)
		param->normal = t->normale;
	else
		param->normal = 
		v3_normalize(&param->normal);
	return (TRUE);
}
BOOL	hit_triangle(void *obj, const t_ray ray, const double t[2], t_hit *param)
{
	t_triangle *t;
	double sol;
	t_vec3	oc;

	t = (t_triangle*)obj;
	oc = v3_sub_vec_(ray.dir, t->vertex);
	if (v3_dot_double_(ray.dir, t->normale) != 0)
	{
		sol = -1 * (v3_dot_double_(oc, t->normale)) / v3_dot_double_(ray.dir, t->normale);
		 if (d.sol > 0. && (d.sol < t[1] && d.sol > t[0]))
			 return (normal_triangle(t, ray, sol, param));
	}
	return (FALSE);
}

BOOL    hit_triangle(void *obj, const t_ray ray, const double t[2], t_hit *param)
{
	t_triangle *t;
	t_vec3 c0c1;
	t_vec3 c0c2;
	t_vec3	N;
	t_vec3	P;
	t_vec3	C;
	t_vec3	edge0;
	t_vec3	vp0;
	t_vec3	edge1;
	t_vec3	vp1;
	t_vec3	edge2;
	t_vec3	vp2;
	double	notraydirec;
	double	d;
	double	sol;

	t = (t_triangle*)obj;
	c0c1 = v3_sub_vec_(t->corner1, t->vertex);
	c0c2 = v3_sub_vec_(t->corner2, t->vertex);
	N = v3_cross_vec_(c0c1, c0c2);

	notraydirec = v3_dot_double_(N, ray.dir);
	if (d.sol > t[1] && d.sol < t[0])
		return (FALSE);
	d = v3_dot_double_(N, t->vertex);
	sol = v3_dot_double_(N, ray.orig) + d;
	if (t < 0)
		return (FALSE);
	P = v3_add_vec_(ray.orig, v3_scale_vec_(ray.dir, t);
	edge0 = v3_sub_vec_(t->corner1, t->vertex);
	vp0 = v3_sub_vec_(P, t->vertex);
	C = v3_cross_vec_(edge0, vp0);
	if (v3_dot_double_(N, C) < 0)
		return (FALSE);
	
