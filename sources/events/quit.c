/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 14:04:06 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/24 10:54:46 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		quit_rt(t_rt *rt)
{
	ft_printf("-- Exit! Cleaning memory --\n");
	SDL_FreeSurface(rt->sr_view);
	SDL_FreeSurface(rt->sr_menu);
	SDL_FreeSurface(rt->s_process);
	SDL_DestroyTexture(rt->tx_view);
	SDL_DestroyTexture(rt->tx_menu);
	SDL_DestroyTexture(rt->tx_process);
	esdl_exit(rt->esdl);
}
