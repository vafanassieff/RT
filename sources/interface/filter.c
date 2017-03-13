/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 15:27:05 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/12 17:37:49 by vafanass         ###   ########.fr       */
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

/*int	min(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int		max(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

void	filter_motionblur(t_rt *rt, t_filtervalue *f)
{
	int		filterx;
	int		filtery;
	int		imagex;
	int		imagey;
	int		maricewidth;
	int		matriceheigth;
	double r;
	double g;
	double b;
	double factor;
	double bias;

	int red;
	int green;
	int	blue;

	maricewidth = 5;
	matriceheigth = 5;
	factor = 1.0;
	bias = 0;
	double matrice[5][5] =
	{
		0, 0, 1, 0, 0,
		0, 1, 1, 1, 0,
		1, 1, 1, 1, 1,
		0, 1, 1, 1, 0,
		0, 0, 1, 0, 0,
	};
	f->pixels = (Uint32 *)rt->sr_view->pixels;
	f->y = 0;
	while (++f->y < rt->sr_view->h)
	{
		f->x = -1;
		 while (++f->x < rt->sr_view->w)
		{
			r = 0.0, g = 0.0,  b = 0.0;
			filtery = 0;
			while (filtery < 5)
			{
				filterx = 0;
				while (filterx < 5)
				{
					imagex = (f->x - maricewidth / 2 + filterx + rt->sr_view->w) % rt->sr_view->w;
					imagey = (f->y - matriceheigth / 2 + filtery + rt->sr_view->h) % rt->sr_view->h;
					f->pixel = f->pixels[imagey * rt->sr_view->w + imagex];
					f->b = f->pixel >> 16 & 0xFF;
					f->g = f->pixel >> 8 & 0xFF;
					f->r = f->pixel & 0xFF;
					b += f->b * matrice[filtery][filterx];
					g += f->g * matrice[filtery][filterx];
					r += f->r * matrice[filtery][filterx];
				}
				
			}
				red = min(max((int)(factor * r + bias), 0), 255);
				green = min(max((int)(factor * g + bias), 0), 255);
				blue = min(max((int)(factor * b + bias), 0), 255);
				f->pixel = (0xFF << 24) | (blue << 16) | (green << 8) | red;
				esdl_put_pixel(rt->s_process, f->x, f->y, (int)f->pixel);
			}
	}
}*/
