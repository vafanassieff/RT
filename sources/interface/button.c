/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:22:20 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/20 18:05:24 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	flash_snap(t_rt *rt, int flag)
{
	static int	hex = 0x00ffffff;
	int			i;

	i = 0;
	while (i++ < 3)
	{
		if (flag == 0)
			hex += 0x22000000;
		else
			hex -= 0x22000000;
		esdl_clear_surface(rt->s_process, NULL, hex, NULL);
		rt->render = TRUE;
		display_rt(rt);
	}
}

void		button_render(void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if (!rt->suspend)
	{
		rt->limit_iter = rt->iter->s + 1;
		rt->suspend = TRUE;
	}
	else
		rt->suspend = FALSE;
}

void		button_filter(void *param)
{
	t_rt			*rt;
	t_filtervalue	f;
	t_matrixf		*t;
	static	int		reset;

	t = malloc(sizeof(t_matrixf));
	rt = (void*)param;
	rt->suspend = TRUE;
	if (reset >= 4)
		reset = 0;
	if (reset == 0)
		filter_sepia(rt, &f);
	else if (reset == 1)
		filter_greyscale(rt, &f);
	else if (reset == 2)
		filter_negative(rt, &f);
	else if (reset == 3)
	{
		choose_matrice(t);
		int x;
		int y;
		y = 0;
		x = -1;
		printf("\n\n");
		while (x++ < (t->size + 1) * (t->size + 1) - 1)
		{
			printf("%d ", (int)t->matrice[x]);
			y++;
			if (y == t->size + 1)
			{
				printf("\n");
				y = 0;
			}
		}
		filter_matrice(rt, &f, *t);
	}
	reset++;
	rt->render = TRUE;
	display_rt(rt);
}

void		button_snap(void *param)
{
	static int	i = 0;
	char		name[32];
	t_rt		*rt;

	rt = (t_rt*)param;
	if (rt->suspend)
	{
		flash_snap(rt, 0);
		sprintf(name, "snapshot-" "%s" "_%0.2d" ".BMP", rt->seed, i++);
		SDL_SaveBMP(rt->sr_view, name);
		flash_snap(rt, 1);
	}
}
