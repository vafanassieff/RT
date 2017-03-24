/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:33:08 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/23 13:14:53 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parabloid	*new_paraboloid(t_vec3 vertex, t_vec3 center, double k)
{
	t_parabloid *p;
	if (!(p = malloc(sizeof(t_parabloid))))
		return (0);
	v3_normalize(&vertex);
	p->vertex = vertex;
	p->center = center;
	p->k = k;
	return (p);
}

BOOL	normal_paraboloid(const t_parabloid *p, const t_ray ray, t_hit *param, double sol)
{
	double	m;
	t_vec3	tmp;

	param->t = sol;
	param->pos = ray_point_at(ray, param->t);
	m = v3_dot_double_(v3_sub_vec_(param->pos, p->center), p->vertex);
	tmp = v3_scale_vec_(p->vertex, p->k + m);
	param->normal = v3_sub_vec_(param->pos, v3_sub_vec_(p->center, tmp));
	v3_normalize(&param->normal);
	return (TRUE);
}

BOOL	hit_parabloid(void *obj, const t_ray ray, const double t[2], t_hit *param)
{
	t_parabloid	*p;
	double	a;
	double	b;
	double	c;
	double discriminant;
	t_vec3	oc;
	double	sol;

	p = (t_parabloid*)obj;
	oc = v3_sub_vec_(ray.orig, p->center);
	a = v3_dot_double_(ray.dir, ray.dir) -
	(v3_dot_double_(ray.dir, p->vertex) * v3_dot_double_(ray.dir, p->vertex));
	b = 2 * (v3_dot_double_(ray.dir, oc) - ((v3_dot_double_(ray.dir, p->vertex)) *
	((v3_dot_double_(oc, p->vertex) + 2 * p->k))));
	c = v3_dot_double_(oc, oc) - ((v3_dot_double_(oc, p->vertex) *
	(v3_dot_double_(oc, p->vertex) + (4 * p->k))));
	discriminant = (b * b) - (4 * a * c);
	if (discriminant >= 0)
	{
		sol = ((-b - sqrt(discriminant)) / (2.0 * a));
		if (sol < t[1] && sol > t[0])
			return (normal_paraboloid(p, ray, param, sol));
		sol = ((-b + sqrt(discriminant)) / (2.0 * a));
		if (sol < t[1] && sol > t[0])
			return (normal_paraboloid(p, ray, param, sol));
	}
	return (FALSE);
}
