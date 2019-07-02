/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:27:39 by mmasyush          #+#    #+#             */
/*   Updated: 2019/06/27 13:27:40 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

Mix_Music	*load_music(char *path)
{
	Mix_Music *load;

	load = Mix_LoadMUS(path);
	if (load == NULL)
		stop("\033[22;31mERROR: failed to load music");
	return (load);
}

Mix_Chunk	*load_sound(char *path)
{
	Mix_Chunk *load;

	load = Mix_LoadWAV(path);
	if (load == NULL)
		stop("\033[22;31mERROR: failed to load music");
	return (load);
}

void	move_sound(t_sound *sound)
{
	if (!(Mix_Playing(-1)))
		Mix_PlayChannel(-1, sound->steps, 0);
}

void		switch_music(t_sound *sound, SDL_Event ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == SDLK_m)
        {
            printf("KGIUDHGNS");
            printf("%d\n", sound->n);
			play_music(sound, sound->n);
        }
        else if (ev.key.keysym.sym == GREATER && sound->n < 4)
		{
			Mix_HaltMusic();
			sound->n += 1;
			play_music(sound, sound->n);
		}
		else if (ev.key.keysym.sym == LESER && sound->n > 0)
		{
			Mix_HaltMusic();
			sound->n -= 1;
			play_music(sound, sound->n);
		}
	}
}

void		play_music(t_sound *sound, int n)
{
	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(sound->music[n], -1);
	else if (Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void	load_sounds(t_sound *sound)
{
    sound->n = 0;
    sound->music[0] = load_music("./materials/sounds/classic.mp3");
	sound->steps = load_sound("./materials/sounds/step.wav");
	sound->jump = load_sound("./materials/sounds/jump.wav");
	sound->run = load_sound("./materials/sounds/run.wav");
}