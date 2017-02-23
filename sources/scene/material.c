/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_material.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:46:01 by qfremeau          #+#    #+#             */
/*   Updated: 2017/02/23 18:48:07 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
  Function pointers for scatter type not well working for now
*/

t_vec3		reflect(const t_vec3 v, const t_vec3 n)
{
	return (v3_sub_vec_(v, v3_scale_vec_(n, 2. * v3_dot_double_(v, n))));
}

BOOL		refract(const t_vec3 v, const t_vec3 n, double ni_over_nt,
			t_vec3 *refracted)
{
	t_vec3		uv;
	double		discriminant;
	double		dt;

	uv = v3_unit_vec_(v);
	dt = v3_dot_double_(uv, n);
	discriminant = 1. - ni_over_nt * ni_over_nt * (1. - dt * dt);
	if (discriminant > 0.)
	{
		*refracted = v3_sub_vec_(v3_scale_vec_(v3_sub_vec_(uv, v3_scale_vec_
		(n, dt)), ni_over_nt), v3_scale_vec_(n, sqrt(discriminant)));
		return (TRUE);
	}
	else
		return (FALSE);
}

t_mat		*new_material(t_vec3 albedo, double t, t_texture *texture)
{
	t_mat		*m;

	m = malloc(sizeof(t_mat));
	m->albedo = albedo;
	m->t = t;
	m->m_text = texture;
	return (m);
}

BOOL		scatter_lambertian(const t_ray ray, const t_hit param,
			t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3		target;

	(void)ray;
	target = v3_add_vec_(v3_add_vec_(param.pos, param.normal),
	random_in_unit_sphere());
	*scattered = new_ray(param.pos, v3_sub_vec_(target, param.pos));
	if (param.material->m_text->type_texture == TEXT_IMAGE)
	{
		double	u;
		double	v;
		get_sphere_uv(v3_div_vec_(v3_sub_vec_(param.pos, v3_(0., 2., 0.)), 2.),&u, &v);
		*attenuation = image_texture_value(param.material->m_text->data, u, v);
	}
	else
		*attenuation = param.material->albedo;
	return (TRUE);
}

BOOL		scatter_metal(const t_ray ray, const t_hit param,
			t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3		reflected;

	reflected = reflect(v3_unit_vec_(ray.dir), param.normal);
	*scattered = new_ray(param.pos, v3_add_vec_(reflected, v3_scale_vec_
	(random_in_unit_sphere(), param.material->t)));
	*attenuation = param.material->albedo;
	return ((v3_dot_double_(scattered->dir, param.normal) > 0) ? TRUE : FALSE);
}

BOOL		scatter_dielectric(const t_ray ray, const t_hit param, \
			t_vec3 *attenuation, t_ray *scattered)
{
	(void)ray;
	(void)param;
	(void)attenuation;
	(void)scattered;
	return (FALSE);
}

BOOL		scatter_none(const t_ray ray, const t_hit param,
			t_vec3 *attenuation, t_ray *scattered)
{
	(void)ray;
	(void)param;
	(void)attenuation;
	(void)scattered;
	return (FALSE);
}
