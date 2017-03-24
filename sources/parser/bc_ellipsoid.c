/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bc_ellipsoid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:33:06 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/22 15:54:53 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		bc_ellipsoid(t_scene *s, t_parser *p, char *line)
{
	if (p->i_obj >= p->lim_obj || p->i_obj < 0)
	{
		ft_printf("XML %s ERROR - Can't assign more or less (%d) ellipsoid than "
		"initiated at line %d: '%s'\n", __FUNCTION__, p->i_obj, p->l, line);
		exit(-1);
	}
	if (check_opt(p->opt) != E_TAB_ELLIPSOID || p->mat == FALSE)
	{
		ft_printf("XML %s ERROR - Some flags are missing within <ellipsoid>"
		"balise"
		" for objet %d at line %d: %s\n", __FUNCTION__, p->i_obj, p->l, line);
		exit(-1);
	}
	s->obj[p->i_obj] = new_object(s->obj[p->i_obj].p_obj,
	s->obj[p->i_obj].type_obj,
	s->obj[p->i_obj].p_mat, s->obj[p->i_obj].p_mat->type_mat);
	s->this_obj = &s->obj[p->i_obj];
	s->sizeof_obj = p->i_obj + 1;
	p->f = (void*)&bo_void;
	p->opt = 0;
	p->mat = FALSE;
	p->lim_mat = 0;
	p->obj = -1;
	p->same--;
	ft_printf("\t- Ellipsoid[%d] Initiated\n", s->sizeof_obj);
}

void		bo_ellipsoid(t_scene *s, t_parser *p, char *line)
{
	check_objsame(p, line, "ellipsoid");
	p->i_obj++;
	if (p->i_obj >= p->lim_obj)
	{
		p->lim_obj += 8;
		if ((s->obj = (t_obj*)realloc(s->obj, p->lim_obj * sizeof(t_obj)))
			== NULL)
		{
			ft_printf("Realloc %s ERROR - Something went wrong trying to "
			"realloc the given structure at object %d\n", __FUNCTION__,
			p->i_obj);
			exit(-1);
		}
	}
	s->obj[p->i_obj].p_obj = (void*)new_ellipsoid(v3_(0., 0., 0.),
	v3_(0., 1., 0.), 1.0, 4.0);
	s->obj[p->i_obj].type_obj = OBJ_ELLIPSOID;
	p->f = (void*)&bo_void;
	p->opt |= p->byte[E_TAB_ELLIPSOID];
	p->obj = p->i_obj;
	p->opt_m = 0;
}
