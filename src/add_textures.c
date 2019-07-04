/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:37:02 by mmasyush          #+#    #+#             */
/*   Updated: 2019/07/04 13:37:03 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	textline_draw(int y1, int y2, t_render *r, t_texture *t)
{
	t->xscale1 = HFOV / r->v1.y;
	t->xscale2 = HFOV / r->v2.y;
	t->x1 = WIN_WIDTH / 2 - (r->v1.x * t->xscale1);
	t->x2 = WIN_WIDTH / 2 - (r->v2.x * t->xscale2);

	t->percent = (r->win_x - t->x1) / (t->x2 - t->x1);
	t->x_text = (t->wall_tex[3]->w * t->x_split * t->percent) / ((1 - t->percent) * r->v2.y / r->v1.y + t->percent); // x_tex = a * w / ((1 - a) * z2 / z1 + a)
	t->x_text %= t->wall_tex[3]->w;
	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = min(y2, WIN_HEIGHT - 1);
	t->y_point = (r->zb == r->za) ? 0 : (double)(r->win_y - r->za) / (r->zb - r->za);
	t->dy_point = (r->zb == r->za) ? 0 : 1.0 / (r->zb - r->za); // derivation of y_point
	while(r->win_y < t->wall_end)
	{
		t->y_text = t->y_point * t->wall_tex[3]->h * t->y_split;
			t->color = pix_from_text(t->wall_tex[3], t->x_text, t->y_text % t->wall_tex[3]->h);
			
		if (t->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = t->color;
		r->win_y++;
		t->y_point += t->dy_point;
	}
}

void	draw_line_of_sprite(t_sprite_render *sr, SDL_Surface *sprtext, t_render *render) //copyrighted from wall texture drawing
{
	int		x_text;
	int		wall_end;
	float	y_point;
	int		y_text;
	Uint32	color;
	float	x1;
	float	x2;
	float	percent;
	float	xscale1;
	float	xscale2;
	float	dy_point;

	xscale1 = HFOV / sr->v1.y;
	xscale2 = HFOV / sr->v2.y;
	x1 = WIN_WIDTH / 2 - (sr->v1.x * xscale1);
	x2 = WIN_WIDTH / 2 - (sr->v2.x * xscale2);
	percent = (sr->win_x - x1) / (x2 - x1);
	x_text = (sprtext->w * percent) / ((1 - percent) * sr->v2.y / sr->v1.y + percent); // a * w / ((1 - a) * z2 / z1 + a)
	sr->win_y = clamp(sr->za, sr->clmp_top, sr->clmp_bot);
	wall_end = clamp(sr->zb, sr->clmp_top, sr->clmp_bot);
	y_point = (sr->zb == sr->za) ? 0 : (double)(sr->win_y - sr->za) / (sr->zb - sr->za);
	dy_point = (sr->zb == sr->za) ? (0) : (1.0 / (sr->zb - sr->za)); // derivation of y_point
	while(sr->win_y < wall_end)
	{
		y_text = y_point * sprtext->h;
		color = pix_from_text(sprtext, x_text, y_text);
		if (color != 0)
			render->pix[sr->win_y * WIN_WIDTH + sr->win_x] = color;
		sr->win_y++;
		y_point += dy_point;
	}
}