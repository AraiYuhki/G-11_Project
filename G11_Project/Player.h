//================================================================================
//	プレイヤークラス
//	Author:Tsukagoshi Toshiyuki
//================================================================================
#pragma once 

//================================================================================
//	include
//================================================================================
#include "Eatan.h"

//================================================================================
//	プレイヤークラス
//================================================================================
class Player :public Eatan
{
public:
	

	static Player* Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXCOLOR &color, int priority = 0);

	Player(int priority = 0);
	~Player(){}

	void Update();
	void Draw();

	

private:
	D3DXVECTOR3 OldPos;
};

