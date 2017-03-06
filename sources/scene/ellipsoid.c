/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:33:08 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/06 17:57:43 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_paraboloid	*new_paraboloid(t_vec3 vertex, t_vec3 center, double k)
{
	t_paraboloid *p;
	if (!(p = malloc(sizeof(t_paraboloid))))
		return (0);
	v3_normalize(&vertex);
	p->vertex = vertex;
	p->center = center;
	p->k = k;
	return (p);
}

BOOL	normal_paraboloid(const t_paraboloid *p, const t_ray ray, t_hit *param, double sol, double m)
{
	param->t = sol;
	param->pos = ray_point_at(ray, param->t);
	param->normal = v3_sub_vec_(v3_sub_vec_(v3_scale_vec_(p->vertex, p->k + m), p->center), param->pos);
	v3_normalize(&param->normal);
	//printf("norm x %f y %f z %f\n", param->normal.x, param->normal.y, param->normal.z);
	return (TRUE);
}

BOOL	hit_paraboloid(void *obj, const t_ray ray, const double t[2], t_hit *param)
{
	t_paraboloid	*p;
	double	a;
	double	b;
	double	c;
	double discriminant;
	t_vec3	oc;
	double	sol;
	double	m;
	double	ti;
	t_vec3	pc;

	p = (t_paraboloid*)obj;
	oc = v3_sub_vec_(ray.orig, p->center);
	a = v3_dot_double_(ray.dir, ray.dir) - (v3_dot_double_(ray.dir, p->vertex) * v3_dot_double_(ray.dir, p->vertex));
	b = 2 * (v3_dot_double_(ray.dir, oc) - v3_dot_double_(ray.dir, p->vertex) * ((v3_dot_double_(oc, p->vertex) + 2 * p->k)));
	c = v3_dot_double_(oc, oc) - (v3_dot_double_(oc, p->vertex) * (v3_dot_double_(oc, p->vertex) + 4 * p->k));
	discriminant = (b * b) - (4.0 * a * c);
	if (discriminant >= 0)
	{
		sol = (-b - (sqrt(discriminant) / (2.0 * a)));
		if (sol < t[1] && sol > t[0])
		{
			ti =  -v3_dot_double_(oc, p->vertex) / v3_dot_double_(ray.dir, p->vertex);
			pc = v3_add_vec_(v3_scale_vec_(ray.dir, ti), oc);
			m = v3_dot_double_(pc, p->vertex);
			m = 1.;
			normal_paraboloid(p, ray, param, sol, m);
		}
		sol = (-b + (sqrt(discriminant) / (2.0 * a)));
		if (sol < t[1] && sol > t[0])
		{
			ti =  -v3_dot_double_(oc, p->vertex) / v3_dot_double_(ray.dir, p->vertex);
			pc = v3_add_vec_(v3_scale_vec_(ray.dir, ti), oc);
			m = v3_dot_double_(pc, p->vertex);
			m = 1.;
			normal_paraboloid(p, ray, param, sol, m);
		}
	}
	return (FALSE);
}
