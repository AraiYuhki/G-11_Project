//================================================================================
//	プレイヤークラス
//	Author:Tsukagoshi Toshiyuki
//================================================================================

//================================================================================
//	include
//================================================================================
#include "Player.h"
#include "Shader2D.h"
#include "Texture.h"
#include "Input\VC.h"

//================================================================================
//	定数
//================================================================================
//画像サイズ
#define PLAYER_TEX_SIZE_WIDTH	(100)
#define PLAYER_TEX_SIZE_HEIGHT	(100)

//アニメーションの分割数
#define PLAYER_PARTITION_STOP	(1)			
#define PLAYER_PARTITION_MOVE	(1)
#define PLAYER_PARTITION_EAT	(1)
#define PLAYER_PARTITION_GLAD	(1)

//アニメーションのスピード
#define PLAYER_ANIMATION_SPEED_STOP	(0.03f)
#define PLAYER_ANIMATION_SPEED_MOVE	(0.03f)
#define PLAYER_ANIMATION_SPEED_EAT	(0.03f)
#define PLAYER_ANIMATION_SPEED_GLAD	(0.03f)

//移動スピード
#define PLAYER_SPEED		(0.5f)

//慣性の減衰率
#define PLAYER_INERTIA		(0.95f)

//上下に揺れる移動量
#define PLAYER_SWAY_HEIGHT		(0.02f)

//上下に揺れるスピード
#define PLAYER_SWAY_SPEED		(0.04f)



//================================================================================
//	コンストラクタ
//================================================================================
Player::Player(int Priority)
{
	//ステータスの初期化
	_State = PLAYER_STATE_STOP;			//停止状態で生成
	MaxPartition = 0;
	SwayCount = 0;


	AnimationPartition[PLAYER_STATE_STOP] = PLAYER_PARTITION_STOP;
	AnimationPartition[PLAYER_STATE_MOVE] = PLAYER_PARTITION_MOVE;
	AnimationPartition[PLAYER_STATE_EAT]  = PLAYER_PARTITION_EAT;
	AnimationPartition[PLAYER_STATE_GLAD] = PLAYER_PARTITION_GLAD;

	AnimationSpeed[PLAYER_STATE_STOP] = PLAYER_ANIMATION_SPEED_STOP;
	AnimationSpeed[PLAYER_STATE_MOVE] = PLAYER_ANIMATION_SPEED_MOVE;
	AnimationSpeed[PLAYER_STATE_EAT]  =	PLAYER_ANIMATION_SPEED_EAT;
	AnimationSpeed[PLAYER_STATE_GLAD] = PLAYER_ANIMATION_SPEED_GLAD;

}

//================================================================================
//	プレイヤー生成
//================================================================================
Player* Player::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXCOLOR &color, int priority)
{
	Player* player = new Player(priority);
	player->_Pos = pos;
	player->_Size = D3DXVECTOR3(size.x, size.y, 0);
	player->_Color = color;

	player->SetTexture(GetTexture(TEX_EFFECT_GEAR));


	//アニメーション枚数の最大値
	for (int i = 0; i < PLAYER_STATE_MAX; i++)
	{
		player->MaxPartition = max(player->MaxPartition, player->AnimationPartition[i]);
	}

	return player;
}

//================================================================================
//	更新処理
//================================================================================
void Player::Update()
{
	VC* vc = VC::Instance();

	PLAYER_STATE oldState;		//前フレームの状態
	oldState = _State;

	//****************************************
	//	移動
	//****************************************
	_Speed += D3DXVECTOR3(vc->LStickX(), vc->LStickY(), 0.0f) * PLAYER_SPEED;
	_Speed *= PLAYER_INERTIA;

	//上下にふわふわ移動
	SwayCount += PLAYER_SWAY_SPEED;
	_Speed.y += sinf(SwayCount)*PLAYER_SWAY_HEIGHT;
		
	//****************************************
	//	アニメーション関係
	//****************************************

	//前回と状態が変わっていたらアニメーション用カウンタをリセット
	if (oldState != _State)
	{
		AnimationCount = 0.0f;
	}
	//変更されていなければカウンタの更新
	else
	{
		AnimationCount += AnimationSpeed[_State];
	}

	//テクスチャUVの変更
	SetUV(D3DXVECTOR4((float)(PLAYER_TEX_SIZE_WIDTH*(int)AnimationCount),(float)(PLAYER_TEX_SIZE_HEIGHT*_State), 1.0f / (float)MaxPartition, 1.0f));

	Sprite::Update();
}

//================================================================================
//	描画処理
//================================================================================
void Player::Draw()
{

	Sprite::Draw();
}

//================================================================================
//	ステートの設定
//================================================================================
void Player::SetState(int State)
{
	
}
