/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:14:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 18:15:00 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	change_move(t_vertex *move, t_doom *d, int str, int dir)
{
	if (str == STRAIGHT)
	{
		move->x += d->player.anglecos * MOVE_SPEED * dir;
		move->y += d->player.anglesin * MOVE_SPEED * dir;
	}
	else
	{
		move->x += d->player.anglesin * MOVE_SPEED * dir;
		move->y -= d->player.anglecos * MOVE_SPEED * dir;
	}
	if(!d->game.flying)
		move_sound(&d->sound);
}

static void	movement_keys(t_doom *d)
{
	t_game		*g;
	t_vertex	move;
	const Uint8	*keyboard_state = SDL_GetKeyboardState(0);

	g = &d->game;
	move.x = 0;
	move.y = 0;
	g->moving = keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_A] \
	|| keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_S] \
	|| keyboard_state[SDL_SCANCODE_LSHIFT];
	if (keyboard_state[SDL_SCANCODE_W])
		change_move(&move, d, STRAIGHT, 1);
	if (keyboard_state[SDL_SCANCODE_A])
		change_move(&move, d, STRAFE, 1);
	if (keyboard_state[SDL_SCANCODE_D])
		change_move(&move, d, STRAFE, -1);
	if (keyboard_state[SDL_SCANCODE_S])
		change_move(&move, d, STRAIGHT, -1);
	if (keyboard_state[SDL_SCANCODE_LSHIFT])
		d->game.ducking = 1;
	else
		d->game.ducking = 0;
	g->velocity.x = g->velocity.x * (1 - g->acceleration) + move.x * g->acceleration;
	g->velocity.y = g->velocity.y * (1 - g->acceleration) + move.y * g->acceleration;
}

static void	mouse_rotation(t_doom *d)
{
	int				x;
	int				y;
	t_game			*g;

	g = &d->game; //should it be used?
	SDL_GetRelativeMouseState(&x,&y); //pislya pauzi nabuvae yakogos znachenya mojna postaviti kostilni flag pause?
	d->player.angle += x * SPEED_ROTATION;
	d->player.angle_z = clamp(d->player.angle_z - y * SPEED_ROTATION_Z, -MAX_Z_ANGLE, MAX_Z_ANGLE);
	d->player.anglesin = sinf(d->player.angle);
	d->player.anglecos = cosf(d->player.angle);
}

void		player_events(t_doom *d)
{
	SDL_Event	ev;

	if (!d->game.pause)
	{
		movement_keys(d);
		mouse_rotation(d);
	}
	while (SDL_PollEvent(&ev) && d->game.quit != 1)
	{
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_ESCAPE) 
				d->game.quit = 1;
			else if (ev.key.keysym.sym == SDLK_SPACE && !d->game.pause)
			{
				//printf("velocity z %f\n", d->game.velocity.z);
				if (d->game.ground || d->game.flying)
				{
					if (d->game.velocity.z < MAX_SPEED_UPWARD)
						d->game.velocity.z += 0.6;
					else
						d->game.velocity.z = MAX_SPEED_UPWARD;
					
					d->game.falling = 1;
				}
				if (!(Mix_Playing(1)) && !d->game.flying)
					Mix_PlayChannel(1, d->sound.jump, 0);
			}
			else if (ev.key.keysym.sym == SDLK_f && !d->game.pause)
			{
				printf("Fly mod\n");
				d->game.flying = !d->game.flying;
			}
			if (ev.key.keysym.sym == SDLK_g)
			{
				d->ui.fire = 1;
			}
			if (ev.key.keysym.sym == SDLK_h)
			{
				if(d->game.hp_level < 4)
					d->game.hp_level += 1;
			}
			if (ev.key.keysym.sym == SDLK_k)
			{
				if (d->game.pause == 0)
				{
					d->game.pause = 1;
					SDL_ShowCursor(SDL_ENABLE);
					SDL_SetRelativeMouseMode(SDL_DISABLE);
					SDL_SetWindowGrab(d->sdl.window, 0);
					SDL_BlitScaled(d->texture.pause, 0, d->sdl.surface, 0);
				}
				else
				{
					d->game.pause = 0;
					SDL_ShowCursor(SDL_DISABLE);
					SDL_SetWindowGrab(d->sdl.window, 1);
					SDL_SetRelativeMouseMode(SDL_ENABLE);
				}
			}
		}
		else if (ev.type == SDL_MOUSEBUTTONDOWN && \
				ev.button.button == SDL_BUTTON_LEFT)
		{
			if(d->ui.fire == 0)
				d->ui.fire = 1;
		}
		else if (ev.type == SDL_QUIT)
			d->game.quit = 1;
		switch_music(&d->sound, ev);
	}

}
