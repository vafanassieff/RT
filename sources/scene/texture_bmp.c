/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:56:15 by vafanass          #+#    #+#             */
/*   Updated: 2017/02/23 18:48:09 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_sphere_uv(const t_vec3 p, double *u, double *v)
{
	double phi;
	double theta;

	phi = atan2(p.z, p.x);
	theta = asin(p.y);
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = (theta + M_PI / 2) / M_PI;
}

t_vec3 image_texture_value(SDL_Surface *data, double u, double v)
{
	int	nx;
	int	ny;
	int	i;
	int	j;
	float	r;
	float	g;
	float	b;
	uint8_t ri;
	uint8_t gi;
	uint8_t bi;
	uint32_t pixel;

	nx = data->w;
	ny = data->h;
	i = u * nx;
	j = (1 - v) * ny - 0.001;
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (i > nx - 1)
		i = nx - 1;
	if (j > ny - 1)
		j = ny - 1;
	pixel = *((uint32_t*)data->pixels + i + nx * j);
	SDL_GetRGB(pixel, data->format , &ri, &gi, &bi);
	r = ri / 255.0;
	g = gi / 255.0;
	b = bi / 255.0;
	
	return(v3_(r, g, b));
}
