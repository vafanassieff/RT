/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 22:19:12 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/23 14:24:09 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		default_obj(t_scene *scene)
{
	t_mat *white = new_material(v3_(0.73, 0.73, 0.73), 0.0);
	t_mat *green = new_material(v3_(0.12, 0.45, 0.15), 0.0);
	t_mat *red = new_material(v3_(0.65, 0.05, 0.05), 0.0);
	t_mat *light = new_material(v3_(15.0, 15.0, 15.0), 0.0);

	scene->obj[0] = new_object((void*)new_triangle(v3_(-5.0, 0.0, 5.0),v3_(-5.0, 0.0, -5.0), v3_(5.0, 0.0 ,-5.0)),
	OBJ_TRIANGLE, white, MAT_LAMBERT);
	scene->obj[1] = new_object((void*)new_triangle(v3_(-5.0, 0.0, 5.0),v3_(5.0, 0.0, 5.0), v3_(5.0, 0.0 , -5.0)),
	OBJ_TRIANGLE, white, MAT_LAMBERT);
	scene->obj[2] = new_object((void*)new_triangle(v3_(-5.0, 0.0, 5.0),v3_(-5.0, 0.0, -5.0), v3_(5.0, 0.0 ,-5.0)),
	OBJ_TRIANGLE, red, MAT_LAMBERT);
	scene->obj[3] = new_object((void*)new_triangle(v3_(-5.0, 0.0, 5.0),v3_(-5.0, 0.0, -5.0), v3_(5.0, 0.0 ,-5.0)),
	OBJ_TRIANGLE, red, MAT_LAMBERT);
	scene->this_obj = &scene->obj[0];
}

void		default_cam(t_rt *rt, t_scene *scene)
{
	scene->sizeof_cam = 1;
	rt->parser.lim_cam = 1;
	scene->cam = (t_cam*)malloc(scene->sizeof_cam * sizeof(t_cam));
	scene->cam[0] = set_camera(v3_(-10., 3., 0.), v3_(0., 0., 0.), v3_(0., -1.,
	0.), camparam(60., (double)rt->r_view->w / (double)rt->r_view->h, .0,
	v3_lenght_double_(v3_sub_vec_(v3_(13., 2., 3.), v3_(0., 0., 0.)))));
	scene->this_cam = &scene->cam[0];
}

void		default_skybox(t_rt *rt, t_scene *scene)
{
	scene->sizeof_skb = 1;
	rt->parser.lim_skb = 1;
	scene->skybox = (t_skybox*)malloc(scene->sizeof_skb * sizeof(t_skybox));
	scene->skybox[0] = new_skybox(v3_(1., 1., 1.), v3_(0.5, 0.7, 1.0),
	SKYBX_GRADIENT);
	scene->this_skb = &scene->skybox[0];
}
