#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

#define MAX_ENEMIES 30
#define MAX_SPAWNERS 15


enum ENEMY_TYPE
{
	
	NO_TYPE,
	LEFT_WEAPON,
	MOTO_TYPE,
	ENEMY_GRENADE,
	ENEMY_BAZOOKA,
	MOTOLEVEL3,
	COMMANDER,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPE type = ENEMY_TYPE::NO_TYPE;
	iPoint pos;
	int angle;
	int sub_type;
};

struct EnemySpawner {
	EnemyInfo info;
	iPoint pos;
	iPoint absolute_deviation;
	int delay_frames;
	int frames_since_prev_spawn = 0;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPE type, int x, int y, int angle, int sub_type);
	bool AddSpawner(ENEMY_TYPE type, int x, int y, int angle, int sub_type, int delay);
	bool EraseEnemy(Enemy* enemy);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	EnemySpawner* spawners[MAX_SPAWNERS];
	SDL_Texture* sprites;
	

public:
	//Basic enemy animations
	//Enemy left weapon
	Animation e1_forward;
	Animation e1_backward;
	Animation e1_left;
	Animation e1_right;
	Animation e1_up_right;
	Animation e1_up_left;
	Animation e1_down_right;
	Animation e1_down_left;

	bool dead;
};

#endif // __ModuleEnemies_H__