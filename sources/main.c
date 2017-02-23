/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:40:50 by qfremeau          #+#    #+#             */
/*   Updated: 2017/02/22 17:48:07 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Need work on mutex and pthread handling
*/

int			main(int ac, char **av)
{
	(void)			av;
	(void)			ac;
	t_rt			p_rt;
	t_rt			*rt;

	kernel_isopencl();

	/*
	** Init RT and scene while displaying loading
	*/

	rt = &p_rt;
	init_rt(rt);
	loading(rt);
	init_rand(rt);
	init_screen_buffer(rt);
	init_multithread(rt);

	/*
	** Start first render while loading panel is still on screen
	*/

	while (rt->iter->s <= 1)
		render(rt);
	esdl_clear_surface(rt->s_process, NULL, 0x00000000, NULL);

	SDL_SetWindowSize(rt->esdl->eng.win, WIN_RX, WIN_RY);
	SDL_SetWindowMinimumSize(rt->esdl->eng.win, WIN_RX - 400, WIN_RY - 300);
	SDL_SetWindowPosition(rt->esdl->eng.win, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowBordered(rt->esdl->eng.win, TRUE);

	SDL_Delay(100);
	rt->t_view = SDL_CreateTextureFromSurface(rt->esdl->eng.render, rt->s_view);
	display_rt(rt);

	/*
	** Start the rendering and display loop
	*/

	pthread_mutex_init(&rt->mutex, NULL);
	pthread_cond_init(&rt->display_cond, NULL);
	pthread_create(&rt->render_th, NULL, (void*)render_loop, (void*)rt);
	
	rt->suspend = TRUE;
	rt->esdl->eng.input->quit = 0;
	while (rt->esdl->run)
	{
		rt_events(rt, rt->esdl->eng.input);

		display_rt(rt);

		esdl_fps_limit(rt->esdl);
		esdl_fps_counter(rt->esdl);
	}
	return (0);
}
