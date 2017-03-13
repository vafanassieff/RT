/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 19:18:42 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/12 17:40:16 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	default_obj(t_scene *scene)
{
	scene->sizeof_obj = 2;
	scene->obj = (t_obj*)malloc(scene->sizeof_obj * sizeof(t_obj));
	scene->obj[0] = new_object((void*)new_plane(v3_(0., 1., 0.), v3_(0., 0.,
	0.)), OBJ_PLANE, new_material(v3_(1., .2, .2), 0., new_texture(TEXT_NONE, NULL)), MAT_LAMBERT);
	//scene->obj[0] = new_object((void*)new_paraboloid(v3_(0.0, -0.1, 0.), v3_(0., 0., 0.), .1), OBJ_PARABOLOID,
	//new_material(v3_(.9, 0.1, 0.2), 0., new_texture(TEXT_NONE, NULL)), MAT_LAMBERT);
	//scene->obj[0] = new_object((void*)new_ellipsoid(v3_(0., 0., 0.), v3_(0., -1., 0.), 4., 4.), OBJ_ELLIPSOID,
	//new_material(v3_(0.9, 0.2, 0.2), 0., new_texture(TEXT_NONE, NULL)), MAT_LAMBERT);
	//scene->obj[1] = new_object((void*)new_cylinder(v3_(0., 1., 0.), v3_(0., 0., 0.),
	//1., 1.), OBJ_CYLINDER, new_material(v3_(1., 1., 1.), 0., new_texture(TEXT_LINEY, NULL)), MAT_LAMBERT);
	scene->obj[1] = new_object((void*)new_sphere(v3_(5., 2., 0.), 4.),
	OBJ_SPHERE, new_material(v3_(.1, 1., 1.), .0, new_texture(TEXT_IMAGE, "./earthmap.bmp")), MAT_LAMBERT);
	//scene->obj[3] = new_object((void*)new_sphere(v3_(0., 1., 4.), 4.),
	//OBJ_SPHERE, new_material(v3_(-5., .2, -1.), 0., new_texture(TEXT_RAINBOW, NULL)), MAT_LAMBERT);
	//scene->obj[4] = new_object((void*)new_sphere(v3_(-1., .5, -1.), .5),
	//OBJ_SPHERE, new_material(v3_(1., 1., .2), 0.), MAT_LAMBERT);
	//scene->obj[0] = new_object((void*)new_cone(v3_(0.0, 1.0, 0.), v3_(0., 0., 0.), .2, 0.000001),
	//OBJ_CONE, new_material(v3_(.3, .5, .1), 0., new_texture(TEXT_LINEY, NULL)), MAT_LAMBERT);
	scene->this_obj = &scene->obj[0];
}

static void	default_scene(t_rt *rt, t_scene *scene)
{
	scene->sizeof_cam = 1;
	scene->cam = (t_cam*)malloc(scene->sizeof_cam * sizeof(t_cam));
	scene->cam[0] = set_camera(v3_(-10., 1., -10.), v3_(0., 0., 0.), v3_(0., -1.,
	0.), camparam(60., (double)rt->r_view->w / (double)rt->r_view->h, .0,
	v3_lenght_double_(v3_sub_vec_(v3_(13., 2., 3.), v3_(0., 0., 0.)))));
	scene->this_cam = &scene->cam[0];
	default_obj(scene);
	scene->sizeof_skb = 1;
	scene->skybox = (t_skybox*)malloc(scene->sizeof_skb * sizeof(t_skybox));
	scene->skybox[0] = new_skybox(v3_(.5, .4, .1), v3_(.6, 1., 1.),
	SKYBX_GRADIENT);
	scene->this_skb = &scene->skybox[0];
}

t_scene		init_scene(t_rt *rt)
{
	t_scene		scene;

	if (rt->filename != NULL)
		read_xml(rt, &scene);
	//else
		default_scene(rt, &scene);
	return (scene);
}
