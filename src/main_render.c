/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:06:14 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/06 13:06:15 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
//apavlov test commit
void	vertical_line(int x, int y1, int y2, t_render *r, int mid)
{
	y1 = clamp(y1, 0, WIN_HEIGHT - 1);
	y2 = clamp(y2, 0, WIN_HEIGHT - 1);
	while (y1 < y2)
		r->pix[y1++ * WIN_WIDTH + x] = mid;
}

void	prepare_to_rendering(t_render *r, t_doom d)
{
	r->now.num = d.player.sector;
	r->sect = d.map.sectors + r->now.num; //&d.map.sectors[r->now.num];
	r->now.sx1 = 0;
	r->now.sx2 = WIN_WIDTH - 1;
	r->pcos = d.player.anglecos;
	r->psin = d.player.anglesin;
	ft_memset(r->ztop, 0, WIN_WIDTH);
	ft_memset(r->zbottom, WIN_HEIGHT - 1, WIN_WIDTH);
	r->pix = (Uint32*)d.sdl.surface->pixels;
}

void	render_sector(t_render r, t_doom d)
{
	int i;
	//int x_tex = 0;
	t_plane	cplane = r.sect->ceil_plane;
	t_plane	fplane = r.sect->floor_plane;
	t_plane ncplane;
	t_plane nfplane; 
	r.now.num = d.player.sector;
	r.now.sx1 = 0;
	r.now.sx2 = WIN_WIDTH - 1;
	ft_memset(r.ztop, 0, WIN_WIDTH * sizeof(int));
	ft_memset(r.zbottom, WIN_HEIGHT - 1, WIN_WIDTH * sizeof(int));
	r.sect = d.map.sectors + r.now.num; //&d.map.sectors[r->now.num];


	i = -1;
	while (++i < r.sect->num_vert) // wall
	{
		r.t1.x = r.sect->vert[i].x - d.player.coord.x;
		r.t1.y = r.sect->vert[i].y - d.player.coord.y;
		r.t2.x = r.sect->vert[i + 1].x - d.player.coord.x;
		r.t2.y = r.sect->vert[i + 1].y - d.player.coord.y;
		r.v1.x = r.t1.x;
		r.v1.y = r.t1.y;
		r.v2.x = r.t2.x;
		r.v2.y = r.t2.y;
		rotate_vertex_xy(&r.t1, r.psin, r.pcos);
		rotate_vertex_xy(&r.t2, r.psin, r.pcos);

		if (r.t1.y < fabs(r.t1.x) / 4 && r.t2.y < fabs(r.t2.x) / 4)
			continue ; 
		if (r.t1.y < fabs(r.t1.x) / 4 || r.t2.y < fabs(r.t2.x) / 4)
		{
			t_vertex i1 = intersect(r.t1, r.t2, (t_vertex){0, 0}, (t_vertex){-4, 1});
			t_vertex i2 = intersect(r.t1, r.t2, (t_vertex){0, 0}, (t_vertex){4, 1});	
			if (r.t1.y < fabs(r.t1.x) / 4)
			{
				if(i1.y > 0)
					r.t1 = i1;
				else
					r.t1 = i2;
			}
			if (r.t2.y < fabs(r.t2.x) / 4)
			{
				if (i1.y > 0)
					r.t2 = i1;
				else
					r.t2 = i2;
			}
		}
		r.xscale1 = HFOV / r.t1.y;
		r.xscale2 = HFOV / r.t2.y;
		r.zscale1 = VFOV / r.t1.y; //division by 0
		r.zscale2 = VFOV / r.t2.y;
		//printf("%f %f %f %f\n", r.t1.x, r.t1.y, r.t2.x, r.t2.y);
		r.x1 = WIN_WIDTH / 2 - (int)(r.t1.x * r.xscale1);
		r.x2 = WIN_WIDTH / 2 - (int)(r.t2.x * r.xscale2);

		if(r.x1 >= r.x2 || r.x2 < r.now.sx1 || r.x1 > r.now.sx2)
			continue ;
		if (r.sect->neighbors[i] >= 0)
		{
			ncplane = d.map.sectors[(int)r.sect->neighbors[i]].ceil_plane;
			nfplane = d.map.sectors[(int)r.sect->neighbors[i]].floor_plane;
		}
		// printf("%i\t%i\n\n", r.x1, r.x2);
		// SDL_Delay(500);
		r.begin_x = max(r.x1, r.now.sx1);
		r.end_x = min(r.x2, r.now.sx2);
		r.win_x = r.begin_x - 1;
		float	zfloor_v1 = get_z(fplane, r.sect->vert[i].x, r.sect->vert[i].y);
		float	zfloor_v2 = get_z(fplane, r.sect->vert[i + 1].x, r.sect->vert[i + 1].y);
		float	cfloor_v1 = get_z(cplane, r.sect->vert[i].x, r.sect->vert[i].y);
		float	cfloor_v2 = get_z(cplane, r.sect->vert[i + 1].x, r.sect->vert[i + 1].y);
		float	max_height = fmax(cfloor_v1 - zfloor_v1, cfloor_v2 - zfloor_v2);
		float	split = max_height / 5;
		// float perc = (r.y / 10);
		// int color = color_mix(0xFF0000, 0x000000, (perc > 1 ? 1 : perc));
		while (++r.win_x <= r.end_x) // in wall 
		{
			float perc = percent(r.x1 , r.x2 , r.win_x);
			float lp_x = line_point(r.sect->vert[i].x, r.sect->vert[i + 1].x, perc);
			float lp_y = line_point(r.sect->vert[i].y, r.sect->vert[i + 1].y, perc);
			r.zceil  = get_z(cplane, lp_x, lp_y) - d.player.coord.z;
			r.zfloor = get_z(fplane, lp_x, lp_y) - d.player.coord.z;

			r.z1a  = WIN_HEIGHT / 2 - (int)((r.zceil + r.t1.y * d.player.angle_z) * r.zscale1);
			r.z1b = WIN_HEIGHT / 2 - (int)((r.zfloor + r.t1.y * d.player.angle_z) * r.zscale1);
			r.z2a  = WIN_HEIGHT / 2 - (int)((r.zceil + r.t2.y * d.player.angle_z) * r.zscale2);
			r.z2b = WIN_HEIGHT / 2 - (int)((r.zfloor + r.t2.y  * d.player.angle_z) * r.zscale2);
			r.y = (r.win_x - r.x1) * (r.t2.y - r.t1.y) / (r.x2 - r.x1) + r.t1.y;
			r.za = (r.win_x - r.x1) * (r.z2a - r.z1a) / (r.x2 - r.x1) + r.z1a;
			r.c_za = clamp(r.za, r.ztop[r.win_x], r.zbottom[r.win_x]);
			r.zb = (r.win_x - r.x1) * (r.z2b - r.z1b) / (r.x2 - r.x1) + r.z1b;
			r.c_zb = clamp(r.zb, r.ztop[r.win_x], r.zbottom[r.win_x]);
			vertical_line(r.win_x, r.zb + 1, r.zbottom[r.win_x], &r, 0xFFFF00);
			double fl_wall = r.y;
			double fl_player = 0;
			int y = r.zb;
			// while(y <  WIN_HEIGHT - 1)
			// {
			// 	double fl_point = WIN_HEIGHT / (4.0 * y - WIN_HEIGHT);
			// 	double fl_weight = fl_point / fl_wall;
			// 	double currentFloorX = fl_weight * floorXWall + (1.0 - fl_weight) * d.player.coord.x;
       		// 	double currentFloorY = fl_weight * floorYWall + (1.0 - fl_weight) * d.player.coord.y;
			// 	paint->floortex_x = (int)(paint->newfloor_x * 64) % 64;
			// 	paint->floortex_y = (int)(paint->newfloor_y * 64) % 64;

			// }

			vertical_line(r.win_x, r.ztop[r.win_x], r.za - 1, &r, 0x222222); // cell
			
			if(r.sect->neighbors[i] >= 0)
			{
				r.nzceil = get_z(ncplane, lp_x, lp_y) - d.player.coord.z;
				r.nzfloor = get_z(nfplane, lp_x, lp_y) - d.player.coord.z;
				r.nz1a = WIN_HEIGHT / 2 - (int)((r.nzceil + r.t1.y * d.player.angle_z) * r.zscale1);
				r.nz1b = WIN_HEIGHT / 2 - (int)((r.nzfloor + r.t1.y * d.player.angle_z) * r.zscale1);
				r.nz2a = WIN_HEIGHT / 2 - (int)((r.nzceil + r.t2.y * d.player.angle_z) * r.zscale2);
				r.nz2b = WIN_HEIGHT / 2 - (int)((r.nzfloor + r.t2.y * d.player.angle_z) * r.zscale2);

				r.nza = (r.win_x - r.x1) * (r.nz2a - r.nz1a) / (r.x2 - r.x1) + r.nz1a;
				r.nza = clamp(r.nza, r.ztop[r.win_x], r.zbottom[r.win_x]);
				r.nzb = (r.win_x - r.x1) * (r.nz2b - r.nz1b) / (r.x2 - r.x1) + r.nz1b;
				r.nzb = clamp(r.nzb, r.ztop[r.win_x], r.zbottom[r.win_x]);

				//vertical_line(r.win_x, r.za, r.nza - 1, &r, 0xFF0000); // down to sector?
				textline_draw(r.za, r.nza - 1, &r, &d.texture);
				r.ztop[r.win_x] = clamp(max(r.za, r.nza), r.ztop[r.win_x], WIN_HEIGHT - 1);
				//vertical_line(r.win_x, r.nzb + 1, r.zb, &r, 0xA00FF00); // up to sector
				textline_draw(r.nzb + 1, r.zb, &r, &d.texture);
				r.zbottom[r.win_x] = clamp(min(r.zb, r.nzb), 0, r.zbottom[r.win_x]);
			}
			else
			{
				textline_draw(r.c_za, r.c_zb, &r, &d.texture);
			}
		}
	}
}

void	textline_draw(int y1, int y2, t_render *r, t_texture *t)
{
	t->x_split = 4;
	t->y_split = 2;
	r->fog_distance = 20;
	t->x_point = ((double)((r->win_x - r->x1) / (double)(r->x2 - r->x1))) * t->x_split;
	t->x_text = (int)((t->x_point - (int)t->x_point) * (double)WALL_TEXT_WIDTH);
	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = min(y2, WIN_HEIGHT - 1);
	r->fog_perc = (r->y / r->fog_distance);
	printf("x1:%d\nx2:%d\n", r->x1, r->x2);
	SDL_Delay(50);
	while(++r->win_y < t->wall_end)
	{
		t->y_point = ((double)(r->win_y - r->za) / (double)(r->zb - r->za)) * t->y_split;
		t->y_text = (int)((t->y_point - (int)t->y_point) * (double)WALL_TEXT_HEIGHT);
		t->color = pix_from_text(t->wall_tex[0], t->x_text, t->y_text);
		t->color = color_mix(t->color, 0x000000, (r->fog_perc > 1 ? 1 : r->fog_perc));
		r->pix[r->win_y * WIN_WIDTH + r->win_x] = t->color;
	}
}

int		draw_screen(t_doom doom)
{
	t_render	r;

	prepare_to_rendering(&r, doom);
	bzero(r.pix, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
	render_sector(r, doom);
	SDL_UpdateWindowSurface(doom.sdl.window);
	SDL_Delay(10);
	return (0);
}

