/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:36:25 by mmasyush          #+#    #+#             */
/*   Updated: 2019/06/26 16:36:25 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		color_mix(Uint32 start, Uint32 end, float per)
{
	int		r;
	int		g;
	int		b;

	r = line_point((start >> 16) & 0xFF, (end >> 16) & 0xFF, per);
	g = line_point((start >> 8) & 0xFF, (end >> 8) & 0xFF, per);
	b = line_point(start & 0xFF, end & 0xFF, per);
	return ((r << 16) | (g << 8) | b);
}

void	text_walls(int y1, int y2, t_render *r, t_texture *t)
{
    int text = 2;
	float xscale1 = HFOV / r->v1.y;
	float xscale2 = HFOV / r->v2.y;

	float x1 = WIN_WIDTH / 2 - (r->v1.x * xscale1);
	float x2 = WIN_WIDTH / 2 - (r->v2.x * xscale2);
	float percent = (r->win_x - x1) / (x2 - x1);
	t->x_text = ((t->wall_tex[text]->w * t->x_split * percent / r->v2.y) / ((1 - percent) / r->v1.y + percent / r->v2.y));
	t->x_text %= t->wall_tex[text]->w;
	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = min(y2, WIN_HEIGHT - 1);
	r->fog_perc = (r->y / r->fog_distance);
	while(r->win_y++ < t->wall_end - 1)
	{
		t->y_text = ((t->wall_tex[text]->h * t->y_split) * (r->win_y - r->za) / (r->zb - r->za)) % t->wall_tex[text]->h;
		t->color = pix_from_text(t->wall_tex[text], t->x_text, t->y_text);
		if (t->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = color_mix(t->color, \
				0x000000, (r->fog_perc > 1 ? 1 : r->fog_perc));
	}
}

void	text_flats(int y1, int y2, t_render *r, t_texture *t)
{
    int text = 3;

	r->win_x = (int)r->y;
	t->x_point = (r->win_x - WIN_HEIGHT) / ((int)r->y - WIN_HEIGHT);
	t->x_text = ((t->wall_tex[text]->w * t->x_split * percent * r->y) / ((1 - percent) * r->y + percent * r->y));
	t->x_text %= t->wall_tex[text]->w;
	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = min(y2, WIN_HEIGHT - 1);
	r->fog_perc = (r->y / r->fog_distance);
	while(r->win_y++ < t->wall_end - 1)
	{
		t->y_text = ((t->wall_tex[text]->h * t->y_split) * (r->win_y - r->za) / (r->zb - r->za)) % t->wall_tex[3]->h;
		t->color = pix_from_text(t->wall_tex[text], t->y_text, t->x_text);
		if (t->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = color_mix(t->color, \
				0x000000, (r->fog_perc > 1 ? 1 : r->fog_perc));
	}
}