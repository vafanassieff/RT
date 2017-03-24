/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:25:15 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/23 13:37:30 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		random_scene_sphere(t_rt *rt)
{
	t_scene		scene;
	t_vec3		center;
	double		choose_mat;
	int			i;
	int			a;
	int			b;

	scene.sizeof_cam = 1;
	rt->parser.lim_cam = 1;
	scene.cam = (t_cam*)malloc(scene.sizeof_cam * sizeof(t_cam));
	scene.cam[0] = set_camera(v3_(13., 2., 3.), v3_(0., 0., 0.), v3_(0., -1.,
	0.), camparam(20., (double)rt->r_view->w / (double)rt->r_view->h, .1,
	v3_length_double_(v3_sub_vec_(v3_(13., 2., 3.), v3_(0., 0., 0.)))));
	scene.this_cam = &scene.cam[0];
	scene.sizeof_skb = 1;
	rt->parser.lim_skb = 1;
	scene.skybox = (t_skybox*)malloc(scene.sizeof_skb * sizeof(t_skybox));
	scene.skybox[0] = new_skybox(v3_(1., 1., 1.), v3_(.5, .7, 1.),
	SKYBX_GRADIENT);
	scene.this_skb = &scene.skybox[0];
	scene.sizeof_obj = 486;
	rt->parser.lim_obj = 486;
	scene.obj = (t_obj*)malloc(scene.sizeof_obj * sizeof(t_obj));
	scene.obj[0] = new_object((void*)new_sphere(v3_(0., -1000., 0.), 1000.),
	OBJ_SPHERE, new_material(v3_(.5, .5, .5), 0., NULL), MAT_LAMBERT);
	i = 1;
	a = -11;
	while (a < 11)
	{
		b = -11;
		while (b < 11)
		{
			choose_mat = f_rand();
			center = v3_(a + .9 * f_rand(), .2, b + .9 * f_rand());
			if (v3_length(v3_sub_vec_(center, v3_(4., .2, 0.))) > .9)
			{
				if (choose_mat < .8)
					scene.obj[i++] = new_object((void*)new_sphere(center, .2),
					OBJ_SPHERE, new_material(v3_(f_rand() * f_rand(), f_rand() *
					f_rand(), f_rand() * f_rand()), 0., NULL), MAT_LAMBERT);
				else if (choose_mat < .95)
					scene.obj[i++] = new_object((void*)new_sphere(center, .2),
					OBJ_SPHERE, new_material(v3_(.5 * (1 + f_rand()), .5 * (1 +
					f_rand()), .5 * (1 + f_rand())), .5 * f_rand(), NULL), MAT_METAL);
				else
					scene.obj[i++] = new_object((void*)new_sphere(center, .2),
					OBJ_SPHERE, new_material(v3_(1., 1., 1.), 1.5, NULL), MAT_DIELECT);
			}
			++b;
		}
		++a;
	}
	scene.obj[i++] = new_object((void*)new_sphere(v3_(0., 1., 0.), 1.),
	OBJ_SPHERE, new_material(v3_(1., 1., 1.), 1.5, NULL), MAT_DIELECT);
	scene.obj[i++] = new_object((void*)new_sphere(v3_(-4., 1., 0.), 1.),
	OBJ_SPHERE, new_material(v3_(.4, .2, .1), 0., new_texture(TEXT_LINEY, NULL)),
	MAT_LAMBERT);
	scene.obj[i++] = new_object((void*)new_sphere(v3_(4., 1., 0.), 1.),
	OBJ_SPHERE, new_material(v3_(.7, .6, .5), 0., NULL), MAT_METAL);
	scene.this_obj = &scene.obj[i - 1];
	ft_printf("-- Initiated ''Randomized Spheres'' scene --\n");
	return (scene);
}
