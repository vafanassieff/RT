/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:50:44 by vafanass          #+#    #+#             */
/*   Updated: 2017/02/25 17:02:32 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	*select_texture(const UCHAR t)
{
	void	*s;

	if (t == TEXT_IMAGE)
		s = (void *)&surface_value;
	else
		s = NULL;
	return (s);
}

t_texture	*new_texture(const UCHAR type_texture, char *filename)
{
	t_texture	*t;

	t = malloc(sizeof(t_texture));
	t->type_texture = type_texture;
	t->filename = filename;
	t->texture_func = select_texture(type_texture);
	if (t->filename != NULL)
		t->data = SDL_LoadBMP(filename);
	return (t);
}
