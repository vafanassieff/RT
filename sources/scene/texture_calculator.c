/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calculator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:44:51 by vafanass          #+#    #+#             */
/*   Updated: 2017/02/27 15:01:29 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	texture_checkboard(t_vec3 pos, t_vec3 *attenuation)
{
	float	sines;

	sines = sin(10 * pos.x) *  sin(10 * pos.y) *  sin(10 * pos.z);
	if (sines < 0)
		*attenuation = v3_(0.9, 0.1, 0.1);
	else
		*attenuation = v3_(0.9, 0.9, 0.9);
}
