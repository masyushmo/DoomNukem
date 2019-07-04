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
	SDL_BlitSurface(d->texture.hp[d->game.hp_level], 0, d->sdl.surface, &d->texture.hp_r);
	gun_anim(d);
    SDL_BlitSurface(d->texture.visor[0], 0, d->sdl.surface, 0);
	SDL_BlitSurface(d->texture.visor[1], 0, d->sdl.surface, 0);
}

void    gun_anim(t_doom *d)
{
    
    if (d->ui.fire == 0)
		SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
	else if(d->ui.fire > 0)
	{
		int start = SDL_GetTicks();
		if (!(Mix_Playing(2)))
			Mix_PlayChannel(2, d->sound.gun1, 0);
		printf("%d\n", d->ui.fire);
		SDL_BlitSurface(d->texture.gun1[d->ui.fire], 0, d->sdl.surface, &d->texture.gun1_r);
		d->ui.fire = (start / 50) % 21;
	}
}