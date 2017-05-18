﻿#include "ModuleLevel4.h"
#include "ModuleLevel3.h"
#include "ModuleSceneGame.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include <string>
#include "ModuleObjects.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"
#include "EnemyVehicles.h"




ModuleLevel4::ModuleLevel4()
{
	intro = true;
	next = this;
}


ModuleLevel4::~ModuleLevel4()
{
}


bool ModuleLevel4::Start() {
	screen_enemies = 0;
	bool ret = true;
	restart = false;
	App->level = 4;
	App->current_scene = this;
	intro = false;
	background_graphics = App->textures->Load("Images/Mapa4.png", &level_dimensions);

	App->render->camera.x = -20 * SCREEN_SIZE;
	App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;

	//ADD ENEMIES
	if (App->level == 4)
	{
		
	}

	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;�.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;�.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);

	//Enabling modules
	App->player->Enable();
	App->collision->Enable();
	App->objects->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	App->fonts->Enable();

	/*if (App->sound->LoadMusic("Soundtrack/3.Hintergrundmusik 1.wav") == nullptr)
	ret = false;*/
	if (background_graphics == nullptr)
		ret = false;


	/*if (!App->sound->isPlaying()) {
	App->sound->PlayMusic();
	}*/

	/*App->sound->PlaySound(newstart, 0);*/

	return ret;
}

update_status ModuleLevel4::PreUpdate() {

	if (restart) {
		App->fade->FadeToBlack(this, next, 0.0f);
		screen_enemies = 0;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleLevel4::Update() {
	bool ret = true;

	ret = App->render->Blit(background_graphics, 0, 0, nullptr);

	sprintf_s(score_text, 10, "%7d", score);
	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleLevel4::PostUpdate() {

	if (score > top_score)
	{
		top_score = score;
	}
	App->fonts->BlitText(15, 0, font_red, "1up");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 30, 0, font_red, "top score");
	std::string grenade_str = "= ";
	grenade_str.append(std::to_string(App->player->grenades));
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 15, font_white, grenade_str.c_str());
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 103, 8, font_white, score_text);
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 15, 8, font_white, "50000");

	return UPDATE_CONTINUE;
}

bool ModuleLevel4::CleanUp() {
	bool ret = true;
	restart = false;
	App->sound->StopAll();
	App->player->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->objects->Disable();
	App->particles->Disable();
	App->fonts->Disable();
	ret = App->textures->Unload(background_graphics);

	return ret;
}

void ModuleLevel4::onFadeInEnd() {
	restart = false;
}


