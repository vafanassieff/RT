/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:50:44 by vafanass          #+#    #+#             */
/*   Updated: 2017/02/27 15:01:21 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_texture	*new_texture(const UCHAR type_texture, char *filename)
{
	t_texture	*t;

	t = malloc(sizeof(t_texture));
	t->type_texture = type_texture;
	t->filename = filename;
	if (t->filename != NULL && type_texture == TEXT_IMAGE)
		t->data = SDL_LoadBMP(filename);
	return (t);
}

void	texture_sphere(const t_hit  param, t_vec3 *attenuation)
{
	t_vec3		color;
	t_sphere	*s;

	s = (t_sphere *)param.p_obj;
	color = v3_div_vec_(v3_sub_vec_(param.pos, s->center), s->radius);
	sphere_uv(color, &param.material->m_text->u, &param.material->m_text->v);
	*attenuation = surface_value(param.material->m_text->data,
			param.material->m_text->u, param.material->m_text->v);
}

void	texture_it(const t_hit	param, t_vec3 *attenuation)
{
	if (param.material->m_text->type_texture == TEXT_IMAGE)
	{
		if (param.type_obj == OBJ_SPHERE)
			texture_sphere(param, attenuation);
	}
	if (param.material->m_text->type_texture == TEXT_CHECKBOARD)
		texture_checkboard(param.pos, attenuation);
	else
		*attenuation = param.material->albedo;
}
