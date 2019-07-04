/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:14:16 by mmasyush          #+#    #+#             */
/*   Updated: 2019/05/02 18:14:16 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	load_all(t_texture *t, t_sdl *sdl, t_doom *d)
{
	if (!(t->wall_tex = ft_memalloc(sizeof(SDL_Surface*) * 4)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->sky_box = ft_memalloc(sizeof(SDL_Surface*) * 2)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->fonts = ft_memalloc(sizeof(t_font))))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->fonts[0].text_font = TTF_OpenFont("fonts/doom.ttf", 28)))
		stop("\033[22;31mERROR: failed to TTF_OpenFont");
	t->wall_tex[0] = load_tex("./materials/textures/walls/WALL3.png", sdl);
	t->wall_tex[1] = load_tex("./materials/textures/walls/WALL.png", sdl);
	t->wall_tex[2] = load_tex("./materials/textures/walls/WALL-1.png", sdl);
	t->wall_tex[3] = load_tex("./materials/textures/walls/WALL1.png", sdl);
	t->sky_box[0] = load_tex("./materials/textures/sky/sky0.jpg", sdl);
	t->sky_box[1] = load_tex("./materials/textures/sky/sky1.png", sdl);
	t->fonts[0].text_color = (SDL_Color){255, 0, 0, 0};
	t->fonts[0].text_rect = (SDL_Rect){20, 20, 50, 10};
	load_sprites(t, sdl, "./materials/textures/sprites/images.png");
	load_sounds(&d->sound);
	load_ui(t, sdl, d);
}

void	load_ui(t_texture *t, t_sdl *sdl, t_doom *d)
{
	t->gun1_l = 21;
	t->gun2_l = 15;
	t->visor_l = 2;
	t->hp_l = 5;
	t->armor_l = 3;
	if (!(t->gun1 = ft_memalloc(sizeof(SDL_Surface*) * t->gun1_l)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->gun2 = ft_memalloc(sizeof(SDL_Surface*) * t->gun2_l)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->hp = ft_memalloc(sizeof(SDL_Surface*) * t->hp_l)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->armor = ft_memalloc(sizeof(SDL_Surface*) * t->armor_l)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(t->visor = ft_memalloc(sizeof(SDL_Surface*) * t->visor_l)))
		stop("\033[22;31mERROR: failed to malloc textures");
	t->pause = load_tex("./materials/textures/ui/pause.png", sdl);
	t->cross = load_tex("./materials/textures/ui/cross.png", sdl);

	t->gun1[0] = load_tex("./materials/textures/ui/gun1/1.png", sdl);
	t->gun1[1] = load_tex("./materials/textures/ui/gun1/2.png", sdl);
	t->gun1[2] = load_tex("./materials/textures/ui/gun1/2.png", sdl);
	t->gun1[3] = load_tex("./materials/textures/ui/gun1/3.png", sdl);
	t->gun1[4] = load_tex("./materials/textures/ui/gun1/4.png", sdl);
	t->gun1[5] = load_tex("./materials/textures/ui/gun1/5.png", sdl);
	t->gun1[6] = load_tex("./materials/textures/ui/gun1/6.png", sdl);
	t->gun1[7] = load_tex("./materials/textures/ui/gun1/7.png", sdl);
	t->gun1[8] = load_tex("./materials/textures/ui/gun1/8.png", sdl);
	t->gun1[9] = load_tex("./materials/textures/ui/gun1/9.png", sdl);
	t->gun1[10] = load_tex("./materials/textures/ui/gun1/10.png", sdl);
	t->gun1[11] = load_tex("./materials/textures/ui/gun1/11.png", sdl);
	t->gun1[12] = load_tex("./materials/textures/ui/gun1/12.png", sdl);
	t->gun1[13] = load_tex("./materials/textures/ui/gun1/13.png", sdl);
	t->gun1[14] = load_tex("./materials/textures/ui/gun1/14.png", sdl);
	t->gun1[15] = load_tex("./materials/textures/ui/gun1/15.png", sdl);
	t->gun1[16] = load_tex("./materials/textures/ui/gun1/16.png", sdl);
	t->gun1[17] = load_tex("./materials/textures/ui/gun1/17.png", sdl);
	t->gun1[18] = load_tex("./materials/textures/ui/gun1/18.png", sdl);
	t->gun1[9] = load_tex("./materials/textures/ui/gun1/19.png", sdl);
	t->gun1[20] = load_tex("./materials/textures/ui/gun1/20.png", sdl);

	t->visor[0] = load_tex("./materials/textures/ui/hud/visor.png", sdl);
	t->visor[1] = load_tex("./materials/textures/ui/hud/visor1.png", sdl);

	t->hp[0] = load_tex("./materials/textures/ui/hud/hp1.png", sdl);
	t->hp[1] = load_tex("./materials/textures/ui/hud/hp2.png", sdl);
	t->hp[2] = load_tex("./materials/textures/ui/hud/hp3.png", sdl);
	t->hp[3] = load_tex("./materials/textures/ui/hud/hp4.png", sdl);
	t->hp[4] = load_tex("./materials/textures/ui/hud/hp5.png", sdl);

	t->armor[0] = load_tex("./materials/textures/ui/hud/HP.png", sdl);
	t->armor[1] = load_tex("./materials/textures/ui/hud/HP.png", sdl);
	t->armor[2] = load_tex("./materials/textures/ui/hud/HP.png", sdl);
	t->len = t->gun1_l;
	resize_surf(WIN_WIDTH / 3, WIN_HEIGHT / 3, t->gun1, d);
	t->len = t->visor_l;
	resize_surf(WIN_WIDTH, WIN_HEIGHT, t->visor, d);
	t->len = t->hp_l;
	resize_surf(WIN_WIDTH, WIN_HEIGHT / 10, t->hp, d);
	// t->gun2_l = 15;
	// t->hp_l = 5;
	// t->armor_l = 3;
	// temp = texture->gun1[0];
	// // texture->gun1[0] = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH / 2, WIN_HEIGHT / 2, 32, sdl->surface->format->format);
	// SDL_BlitScaled(temp , 0, texture->gun1[0], &gun1);
	// temp = load_tex("./materials/textures/ui/hud/visor.png", sdl);
	// t->visor[0] = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, sdl->surface->format->format);
	// SDL_BlitScaled(temp , 0, texture->visor[0], 0);
	// SDL_FreeSurface(temp);
	// temp = load_tex("./materials/textures/ui/hud/visor1.png", sdl);
	// texture->visor[1] = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, sdl->surface->format->format);
	// SDL_BlitScaled(temp , 0, texture->visor[1], 0);
	// SDL_FreeSurface(temp);
	// system("leaks doom-nukem");
}

void	resize_surf(int w, int h, SDL_Surface** surf, t_doom *d)
{
	SDL_Surface *temp;
	int i;

	i = -1;
	while(++i < d->texture.len)
	{
		temp = surf[i];
		surf[i] = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, d->sdl.surface->format->format);
		SDL_BlitScaled(temp , 0, surf[i], 0);
		SDL_FreeSurface(temp);
	}
}

void	load_sprites(t_texture *texture, t_sdl *sdl, char *path)
{
	SDL_Surface	*surr;
	t_sprite_list	*head; //it must read more then 1 sprite should right present it

	surr = load_tex(path, sdl);
	
	SDL_SetColorKey(surr, SDL_TRUE, SDL_MapRGB(surr->format, 255, 255, 255));
	texture->c_sprt = 3 * 4;
	
	head = split_image_to_sprites(surr, 3, 4); //check for licks and segs
	SDL_FreeSurface(surr);
	
	surr = load_tex("./materials/textures/sprites/painting_flowers.jpg", sdl);
	head->next = split_image_to_sprites(surr, 1, 1);
	SDL_FreeSurface(surr);
	if (head == 0)
	{
		error_message("Texture load error\n");
		exit(1); // im too lazy to exit it right
		return ;
	}
	texture->sprites = head;
}

SDL_Surface	*load_tex(char *path, t_sdl *sdl)
{
	SDL_Surface		*temp;
	SDL_Surface		*texture;

	temp = IMG_Load(path);
	if (temp == NULL)
	{
		SDL_FreeSurface(temp);
		stop("\033[22;31mERROR: failed to load texture");
	}
	texture = SDL_ConvertSurfaceFormat(temp, sdl->surface->format->format, 0);
	SDL_FreeSurface(temp);
	return (texture);
}

Uint32	pix_from_text(SDL_Surface *texture, int x, int y)
{
	Uint32 *ptr;

	ptr = (Uint32 *)texture->pixels;
	return (ptr[(y * texture->w) + x]);
}

int		stop(char *str)
{
	ft_putstr(str);
	exit(1);
}

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