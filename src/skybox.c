/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:28:05 by mmasyush          #+#    #+#             */
/*   Updated: 2019/05/16 13:28:06 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_skybox(t_render *r, t_doom d)
{
	d.sky.win_x = 0;
	d.sky.pos_angle = d.player.anglesin / 0.005556;
	d.sky.pos_max = 5;
	d.sky.text_x = d.sky.pos_angle * d.sky.pos_max;
	if (d.player.anglecos < 0)
		d.sky.text_x = 2048 - d.sky.text_x;
	if (d.sky.text_x < 0)
		d.sky.text_x = SKY_W + d.sky.text_x;
	while (d.sky.win_x < WIN_WIDTH && d.sky.text_x <= SKY_W)
	{
		d.sky.text_x++;
		if (d.sky.text_x < 0)
			d.sky.text_x = SKY_W;
		if (d.sky.text_x > SKY_W)
			d.sky.text_x = 0;
		d.sky.win_y = 0;
		d.sky.text_y = 800 + d.player.angle_z * 160;
		while (d.sky.win_y < WIN_HEIGHT && d.sky.text_y < SKY_H - 1)
		{
			r->pix[d.sky.win_y++ * WIN_WIDTH + d.sky.win_x] =
				pix_from_text(d.texture.sky_box[1], d.sky.text_x, d.sky.text_y);
			d.sky.text_y++;
		}
		d.sky.win_x++;
	}
}
