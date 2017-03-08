/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bc_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 17:23:51 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/08 17:13:58 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		bc_cam(t_scene *s, t_parser *p, char *line)
{
	printf("%s %d\n", __FUNCTION__, p->i_cam);
	if (p->i_cam >= p->lim_cam || p->i_cam < 0)
	{
		ft_printf("XML %s ERROR - Can't assign more or less (%d) cameras than "
		"initiated at line %d: '%s'\n", __FUNCTION__, p->i_cam, p->l, line);
		exit(-1);
	}
	printf("opt flag is %s / %s\n", ft_uitoa_32bit(p->opt), ft_uitoa_32bit(BYTE_CAM | BYTE_POS | BYTE_TARGET));
	if (check_opt(p->opt) != E_TAB_CAM)
	{
		ft_printf("XML %s ERROR - Some flags are missing within <cam> balise "
		"for cam %d at line %d: %s\n", __FUNCTION__, p->i_cam, p->l, line);
		exit(-1);
	}
	s->cam[p->i_cam].param.focus = v3_lenght_double_(v3_sub_vec_(
	s->cam[p->i_cam].param.look_from, s->cam[p->i_cam].param.look_at));
	s->cam[p->i_cam]= set_camera(s->cam[p->i_cam].param.look_from,
	s->cam[p->i_cam].param.look_at, s->cam[p->i_cam].param.v_up,
	s->cam[p->i_cam].param);
	s->this_cam = &s->cam[p->i_cam];
	p->f = (void*)&bo_void;
	p->opt = 0;
}

void		bo_cam(t_scene *s, t_parser *p, char *line)
{
	(void)line;
	p->i_cam++;
	printf("%s %d\n", __FUNCTION__, p->i_cam);
	if (p->i_cam >= p->lim_cam)
	{
		printf("realloc\n");
		p->lim_cam += 4;
		s->cam = (t_cam*)ft_realloc((void*)s->cam, sizeof(t_cam) * p->lim_cam);
	}
	s->cam[p->i_cam].param.aspect = p->ratio;
	s->cam[p->i_cam].param.v_up = v3_(0., -1., 0.);
	s->cam[p->i_cam].param.aperture = 0.;
	s->cam[p->i_cam].param.vfov = 60.;
	p->f = (void*)&bo_void;
	p->opt |= p->byte[E_TAB_CAM];
}
