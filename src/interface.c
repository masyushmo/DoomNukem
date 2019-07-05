/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/07/02 14:58:28 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_ui(t_doom *d)
{
   	SDL_BlitSurface(d->texture.cross, 0, d->sdl.surface, &d->texture.cross_r);
	gun_anim(d);
    SDL_BlitSurface(d->texture.visor[0], 0, d->sdl.surface, 0);
	SDL_BlitSurface(d->texture.visor[1], 0, d->sdl.surface, 0);
}

void    gun_anim(t_doom *d)
{
    
    if (d->ui.gun_num == 0)
	{
    	if (d->ui.fire == 0)
			SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
		else if (d->ui.fire > 0)
		{
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.gun1, 0);
			SDL_BlitSurface(d->texture.gun1[d->ui.fire], 0, d->sdl.surface, &d->texture.gun1_r);
			d->ui.fire = (d->ui.currTime / 50) % 21;
		}
	}
	else if (d->ui.gun_num == 1)
	{
		if (d->ui.start_saw  < 10)
		{
			SDL_BlitSurface(d->texture.gun2[d->ui.start_saw ], 0, d->sdl.surface, &d->texture.gun21_r);
			d->ui.start_saw = (d->ui.currTime / 100) % 11;
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.gun2[0], 0);
		}
		else if (d->ui.start_saw == 10 && d->ui.fire == 1)
		{
			if (d->ui.idle == 0)
			{
				SDL_BlitSurface(d->texture.gun2[14], 0, d->sdl.surface, &d->texture.gun22_r);
				d->ui.idle = 1;
			}
			else if (d->ui.idle == 1)
			{
				SDL_BlitSurface(d->texture.gun2[15], 0, d->sdl.surface, &d->texture.gun22_r);
				d->ui.idle = 0;
			}
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.gun2[2], 0);
		}
		else if (d->ui.start_saw == 10)
		{
			if (d->ui.idle == 0)
			{
				SDL_BlitSurface(d->texture.gun2[10], 0, d->sdl.surface, &d->texture.gun21_r);
				d->ui.idle = 1;
			}
			else if (d->ui.idle == 1)
			{
				SDL_BlitSurface(d->texture.gun2[11], 0, d->sdl.surface, &d->texture.gun21_r);
				d->ui.idle = 0;
			}
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.gun2[1], 0);
		}
	}
	else if (d->ui.gun_num == 2)
	{
    	if (d->ui.fire == 0)
			SDL_BlitSurface(d->texture.dude[0], 0, d->sdl.surface, &d->texture.dude_r);
		else if (d->ui.fire <= 34)
		{
			// if (!(Mix_Playing(2)))
			// 	Mix_PlayChannel(2, d->sound.gun1, 0);
			SDL_BlitSurface(d->texture.dude[d->ui.fire], 0, d->sdl.surface, &d->texture.dude_r);
			d->ui.fire = (d->ui.currTime / 75) % 34;
		}
	}
}