/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:18:48 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/20 14:35:09 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		min(const int a, const int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		max(const int a, const int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	init_filter(t_filtermatrice *m, int size, double factor)
{
	m->matricewidth = size;
	m->matriceheigth = size;
	m->factor = 1.0 / factor;
	m->bias = 0.0;
}

void	reset_rgb(t_filtermatrice *m)
{
	m->r = 0.0;
	m->g = 0.0;
	m->b = 0.0;
	m->filtery = - 1;
}


