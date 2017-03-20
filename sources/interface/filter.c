/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 15:27:05 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/20 18:05:25 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	filter_greyscale(t_rt *rt, t_filtervalue *f)
{
	f->pixels = (Uint32 *)rt->sr_view->pixels;
	f->y = 0;
	while (++f->y < rt->sr_view->h)
	{
		f->x = -1;
		while (++f->x < rt->sr_view->w)
		{
			f->pixel = f->pixels[f->y * rt->sr_view->w + f->x];
			f->b = f->pixel >> 16 & 0xFF;
			f->g = f->pixel >> 8 & 0xFF;
			f->r = f->pixel & 0xFF;
			f->v = 0.212671f * f->r + 0.715160f * f->g + 0.072169f * f->b;
			f->pixel = (0xFF << 24) | (f->v << 16) | (f->v << 8) | f->v;
			esdl_put_pixel(rt->s_process, f->x, f->y, (int)f->pixel);
		}
	}
}

void	filter_sepia(t_rt *rt, t_filtervalue *f)
{
	f->pixels = (Uint32 *)rt->sr_view->pixels;
	f->y = 0;
	while (++f->y < rt->sr_view->h)
	{
		f->x = -1;
		while (++f->x < rt->sr_view->w)
		{
			f->pixel = f->pixels[f->y * rt->sr_view->w + f->x];
			f->b = f->pixel >> 16 & 0xFF;
			f->g = f->pixel >> 8 & 0xFF;
			f->r = f->pixel & 0xFF;
			f->rtmp = f->r * 0.393 + f->g * 0.769 + f->b * 0.189;
			f->gtmp = f->r * 0.349 + f->g * 0.686 + f->b * 0.168;
			f->btmp = f->r * 0.272 + f->g * 0.534 + f->b * 0.131;
			if (f->rtmp > 255)
				f->rtmp = 255;
			if (f->gtmp > 255)
				f->gtmp = 255;
			if (f->btmp > 255)
				f->btmp = 255;
			f->pixel = (0xFF << 24) | ((uint8_t)f->btmp << 16) |
				((uint8_t)f->gtmp << 8) | (uint8_t)f->rtmp;
			esdl_put_pixel(rt->s_process, f->x, f->y, (int)f->pixel);
		}
	}
}

void	filter_negative(t_rt *rt, t_filtervalue *f)
{
	f->pixels = (Uint32 *)rt->sr_view->pixels;
	f->y = 0;
	while (++f->y < rt->sr_view->h)
	{
		f->x = -1;
		while (++f->x < rt->sr_view->w)
		{
			f->pixel = f->pixels[f->y * rt->sr_view->w + f->x];
			f->b = f->pixel >> 16 & 0xFF;
			f->g = f->pixel >> 8 & 0xFF;
			f->r = f->pixel & 0xFF;
			f->b = 255 - f->b;
			f->r = 255 - f->r;
			f->g = 255 - f->g;
			f->pixel = (0xFF << 24) | (f->b << 16) | (f->g << 8) | f->r;
			esdl_put_pixel(rt->s_process, f->x, f->y, (int)f->pixel);
		}
	}
}

void	filter_matrice(t_rt *rt, t_filtervalue *f, t_matrixf t)
{
	t_filtermatrice	m;

	init_filter(&m, t.size, t.factor);
	f->pixels = (Uint32 *)rt->sr_view->pixels;
	f->y = -1;
	int kekus = 0;
	int kek = 0;
	printf("\n\n");
	while (++f->y < rt->sr_view->h)
	{
		f->x = -1;
		while (++f->x < rt->sr_view->w)
		{
			reset_rgb(&m);
			while (m.filtery++ < t.size)
			{
				m.filterx = -1;
				while (m.filterx++ < t.size)
				{
					m.imagex = (f->x - m.matricewidth / 2 + m.filterx + rt->sr_view->w) % rt->sr_view->w;
					m.imagey = (f->y - m.matriceheigth / 2 + m.filtery + rt->sr_view->h) % rt->sr_view->h;
					f->pixel = f->pixels[m.imagey * rt->sr_view->w + m.imagex];
					f->b = f->pixel >> 16 & 0xFF;
					f->g = f->pixel >> 8 & 0xFF;
					f->r = f->pixel & 0xFF;
					m.b += f->b * t.matrice[m.filtery * (t.size + 1) + m.filterx];
					m.g += f->g * t.matrice[m.filtery * (t.size + 1) +  m.filterx];
					m.r += f->r * t.matrice[m.filtery * (t.size + 1) + m.filterx];
					kek++;	
					if (kekus == 0)
						printf("%d ", (int)t.matrice[m.filtery * (t.size + 1)  + m.filterx]);
				}
				  if (kekus == 0)
					  printf("\n");
			}
			kekus = 1;
			m.red = min(max((int)(m.factor * m.r + m.bias), 0), 255);
			m.green = min(max((int)(m.factor * m.g + m.bias), 0), 255);
			m.blue = min(max((int)(m.factor * m.b + m.bias), 0), 255);
			f->pixel = (0xFF << 24) | (m.blue << 16) | (m.green << 8) | m.red;
			esdl_put_pixel(rt->s_process, f->x, f->y, (int)f->pixel);
		}
	}
}
