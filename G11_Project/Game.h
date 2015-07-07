#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "Scene.h"

#define AREA_WIDTH (795.0f)
#define AREA_HEIGHT (875.0f)
#define ITEM_GET_BORDER_LINE (250.0f)

class Pause;
class Gauge;
class ItemManager;
class Sprite;
class Player;
class Item;
class Wall;
class Interface;
class StageManager;

class Game:public Scene
{
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static Player *GetPlayer(void){ return _player;}

	static void SetPause(bool flag){ _PauseFlag = flag; }
	static bool PauseFlag(void){return _PauseFlag; }

#ifdef _DEBUG
	static bool Hit;
#endif

private:
	static bool _PauseFlag;

	static Pause* _Pause;
	static Player	*_player;
	static Item		*_item;
	static StageManager* Stage;


	Interface* _Interface;
};

#endif